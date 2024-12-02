from file_and_multi_lines import read_file_and_split_into_stripped_lines, join_multi_lines, split_multi_lines
from brackets_quotes_comments import find_outside, find_outside_quotes, \
	check_for_comments, get_markers_count, NO_OTHERS_INSIDE
from header import extract_header
from config import NAME, USER, EMAIL
from indent import set_indent_of_function_declr, set_indent_of_var_declr, get_indent_of_variable_block, get_indent_of_prototypes_in_h_file

FIND_OUTSIDE_QUOTES = [('"', '"', NO_OTHERS_INSIDE), ("'", "'", NO_OTHERS_INSIDE)]
FIND_OPEN_CURLY_BRACKETS = [('"', '"', NO_OTHERS_INSIDE), ("'", "'", NO_OTHERS_INSIDE), ("{", "}")]
FIND_OPEN_ROUND_BRACKETS = [('"', '"', NO_OTHERS_INSIDE), ("'", "'", NO_OTHERS_INSIDE), ("(", ")")]

def initiate_positional():
	positional = {

		"enum": False,
		"struct": False,
		"union": False,
		"last_line_enum_struct_union": False,
		"typedef": False,

		"include": False,

		"function": False,
		"function_definition": False,
		"variable_block": False,
		"line_after_variable_block": False,
		
		"one_line_counter": 0
		
	}
	return positional

def split_line_if_has_wrapping_curly_brackets(index, line, lines, in_typedef):
	if ((first_curly := find_outside("{", line, FIND_OUTSIDE_QUOTES))) != -1 \
		and not ((first_curly_closed := find_outside("}", line, FIND_OUTSIDE_QUOTES)) != -1 and \
		first_curly_closed < first_curly):
		if get_markers_count(first_curly, line, FIND_OPEN_ROUND_BRACKETS)[("(", ")")] == 0:
			if line != "{" and line[0] != "#" and line[-1:] != ";":
				sline = line.split("{", 1)
				if sline[1].strip() == "" or sline[1].strip()[0] != "\\":
					lines.insert(index + 1, "{")
					if (sline[1] != ""):
						lines.insert(index + 2, sline[1].strip())
					line = sline[0].strip()
				
	if ((first_curly := find_outside("}", line, FIND_OUTSIDE_QUOTES))) != -1:
		if get_markers_count(first_curly, line, FIND_OPEN_ROUND_BRACKETS)[("(", ")")] == 0:
			if line != "}" and line[0] != "#" and line[-1:] != ";" and not in_typedef:
				sline = line.split("}", 1)
				if sline[0].strip()[-1] != "\\":
					lines.insert(index + 1, "}")
					if (sline[1] != ""):
						lines.insert(index + 2, sline[1].strip())
					line = sline[0].strip()
	return line

def get_indentation_level_for_current_line(previous_line, markers_count, current_line, positional):
	if markers_count != None:
		markers_count[('"', '"', NO_OTHERS_INSIDE)] = 0
		markers_count[("'", "'", NO_OTHERS_INSIDE)] = 0
	markers_count = get_markers_count(None, previous_line, FIND_OPEN_CURLY_BRACKETS, markers_count)
	indentation_level = markers_count[("{", "}")]
	if current_line == "}" or (positional["typedef"] and current_line[:1] == "}") or current_line == "};":
		indentation_level -= 1
	indentation_level += positional["one_line_counter"]
	return markers_count, indentation_level

def update_positional(positional, indentation_level, previous_line, current_line, next_line, is_header):
	if indentation_level == 0 and previous_line is not None	and len(previous_line) > 0:
		if (previous_line == "}" or (positional["typedef"] and previous_line[0] == "}")):
			positional["function"] = False
			positional["function_definition"] = False
			positional["variable_block"] = False
			positional["struct"] = False
			positional["enum"] = False
			positional["union"] = False
			positional["typedef"] = False
		if (current_line == "}" or (positional["typedef"] and current_line[0] == "}")):
			positional["variable_block"] = False
			positional["function_definition"] = False
	if positional["include"]:
		positional["include"] = False

	if indentation_level == 0 and current_line != "" and current_line[0] == "#":
		if current_line[1:].strip()[:len("include")] == "include":
			positional["include"] = True

	if positional["function_definition"]:
		positional["function_definition"] = False

	if indentation_level == 0 and positional["typedef"] and not positional["struct"] and not positional["enum"]:
		positional["typedef"] = False
	if indentation_level == 0 and current_line[:len("typedef ")] == "typedef ":
		positional["typedef"] = True

	if indentation_level == 0 and next_line is not None and next_line == "{":
		if current_line.find("typedef ") != -1 or current_line.find("struct ") != -1 \
			or current_line.find("union ") != -1 or current_line.find("enum ") != -1:
			if current_line.find("typedef ") != -1:
				positional["typedef"] = True
			if current_line.find("struct") != -1:
				positional["struct"] = True
			elif current_line.find("enum ") != -1:
				positional["enum"] = True
			elif current_line.find("union ") != -1:
				positional["union"] = True
		else:
			positional["function"] = True
			positional["function_definition"] = True

	if positional["line_after_variable_block"]:
		positional["line_after_variable_block"] = False
	if (positional["function"] or positional["struct"] or positional["union"]) \
		and indentation_level == 1 and previous_line == "{":
		positional["variable_block"] = True
	if not is_header and positional["variable_block"] and (current_line == "" \
									  or find_outside_quotes("=", current_line) != -1 \
									  or find_outside_quotes("(", current_line) != -1 \
										or find_outside_quotes("}", current_line) != -1):
		positional["variable_block"] = False
		positional["line_after_variable_block"] = True

	
	if [key for key in ["if (", "while (", "if(", "while(", "else if ", "if ", \
					 "else", "while "] if current_line[:len(key)] == key] != [] and \
						next_line is not None and next_line != "{":
		positional["one_line_counter"] += 1
	else:
		positional["one_line_counter"] = 0

	return (positional)

def remove_invalid_tabs(line, positional):
	line_new = []
	for c in line:
		if positional["variable_block"] or (positional["typedef"] and line[-1:] == "}") or positional["function_definition"]:
			line_new.append(c)
		elif c == "\t":
			line_new.append(" ")
		else:
			line_new.append(c)
	return "".join(line_new)

def append_to_corrected_lines(line, lines_corrected, indentation_level, next_line):
	if line != "":
		line = "\t" * indentation_level + line
	lines_corrected.append(line)

	# check for newline after } at EOF
	if next_line is None:
		if line.strip() == "}":
			lines_corrected.append("")
	
	return lines_corrected

def check_spaces_after_keywords(current_line):
	# check for space after keyword
	if (keyword := [key for key in ["if", "while", "else if", "return"] if current_line[:len(key) + 1] == key + "("]) != []:
		keyword = keyword[0]
		current_line = current_line.split(keyword, 1)
		current_line = (keyword + " ").join(current_line)
	# check for return parentheses
	ret_len = len("return ")
	if current_line[:ret_len] == "return " and current_line[:ret_len + 1] != "return ;":
		if current_line[ret_len] != "(":
			current_line = current_line[:ret_len] + "(" + current_line[ret_len:-1] + ")" + current_line[-1]
	if current_line == "return;":
		current_line = "return ;"
	# check for space after break keyword
	if (keyword := [key for key in ["break"] if current_line[:len(key) + 1] == key + ";"]) != []:
		keyword = keyword[0]
		current_line = current_line.split(keyword, 1)
		current_line = (keyword + " ").join(current_line)
	return current_line

def add_valid_tabs(line_index, line, lines, positional, header_prototype_indents, path, indent_level):
	if indent_level == 0 and line != "" and line[-1] == ";" and not positional["typedef"] and not positional["struct"] \
		and not positional["enum"] and not positional["union"]:
		line = set_indent_of_function_declr(line)

	if positional["function_definition"]:
		line = set_indent_of_function_declr(line)

	if positional["variable_block"]:
		indent = get_indent_of_variable_block(line_index, lines)
		line = set_indent_of_var_declr(line, indent)
	
	if  positional["typedef"] and line != "" and line[0] == "}":
		line = line[0] + "\t" + line[1:].strip()
	elif line[:len("typedef")] == "typedef" and line[-1] == ";":
		line = set_indent_of_var_declr(line, 0)

	if path[-2:] == ".h" and indent_level == 0 and line[-1:] == ";" and find_outside_quotes("(", line) != -1:
		line = set_indent_of_function_declr(line, header_prototype_indents)

	return line

# def check_asterix_after_tab(line):
# 	line = line.strip()
# 	ileft = line.find("\t")
# 	iright = line.rfind("\t") + 1
# 	left = line[:ileft]
# 	middle = line[ileft:iright]
# 	right = line[iright:]
# 	if left[-1] == "*":
# 		left = left[:-1]
# 		right = "*" + right
# 	return(left + middle + right)


def check_asterix_after_space(line, middle_space = None):
	line = line.strip()
	begin, end = get_right_space_boundary(line)
	if begin is None or end is None:
		return line
	left = line[:end + 1]
	middle = line[end + 1:begin + 1]
	right = line[begin + 1:]
	if left[-1] == "*":
		left = left[:-1]
		right = "*" + right
	if middle_space is None:
		return(left + middle + right)
	else:
		return(left + middle_space + right)


def get_right_space_boundary(text):
	begin = None
	end = None
	for index, c in enumerate(reversed(text)):
		if begin is None and c.isspace():
			begin = len(text) - index - 1
		if begin is not None and not c.isspace():
			end = len(text) - index - 1
			break
	return (begin, end)

def check_right_position_of_asterix(line, positional):
	if positional["function_definition"]:
		[left, right] = line.split("(", 1)
		left = check_asterix_after_space(left, "\t")
		right = right[:-1]
		args = right.split(",")
		args = [check_asterix_after_space(arg, " ") for arg in args]
		return (left + "(" + ", ".join(args) + ")")

	if positional["variable_block"]:
		return (check_asterix_after_space(line))

	return line

#todo incorporate * for multiplication and for pointer
def check_spaces_around_operators(line):
	line_new = []
	ppc = ""
	pc = ""
	nc = ""
	# remove consecutive spaces
	for i, c in enumerate(line):
		markers_count = get_markers_count(i, line, FIND_OUTSIDE_QUOTES)
		quotes = sum(markers_count.values())
		if quotes:
			line_new.append(c)
			continue
		
		if i < len(line) - 1:
			nc = line[i + 1]
		else:
			nc = ""

		if c == " " and pc == " ":
			pass
		elif c == "," and nc != " ":
			line_new.append(c)
			line_new.append(" ")
		elif (c in "+-/*<>!") and nc == "=":
			if pc != " ":
				line_new.append(" ")
			line_new.append(c)
		elif c == "=":
			if pc != " " and pc not in "+-/*!=<>":
				line_new.append(" ")
			line_new.append(c)
			if nc != "=" and nc != " " and nc != ",":
				line_new.append(" ")
		elif c in ["+", "-", "/"] and \
		pc != "'" and pc != '"' and nc != "'" and nc != '"' and \
		not (c == "+" and (pc == "+" or nc == "+")) and \
		not (c == "-" and ((pc == "-" or nc == "-") or (pc == " " and ppc in "=,") or pc == "")) and \
		not (c == "/" and (pc == "/" or nc == "/")) and \
		not (c == "-" and (pc == "(" or nc == ">")):
					if not pc == " ":
						line_new.append(" ")
					line_new.append(c)
					if not nc == " ":
						line_new.append(" ")
		else:
			line_new.append(c)
			ppc = pc
		pc = line_new[-1]
	line = "".join(line_new)
	return line

def correct_lines_to_norm(lines, path):
	lines_corrected = []

	has_comment = None
	markers_count = None

	previous_line = ""
	next_line = ""

	positional = initiate_positional()
	if path[-2:] == ".h":
		header_prototype_indents = get_indent_of_prototypes_in_h_file(lines)
	else:
		header_prototype_indents = 0
	header_define_indent = 0


	for index, line in enumerate(lines):

		if sum((has_comment := check_for_comments(line, has_comment)).values()) > 0:
			lines_corrected.append(line)
			continue
		line = split_line_if_has_wrapping_curly_brackets(index, line, lines, positional["typedef"])

		markers_count, indentation_level = get_indentation_level_for_current_line(previous_line, markers_count, line, positional)
		if index < len(lines) - 1:
			next_line = lines[index + 1].strip()
		else:
			next_line = None


		positional = update_positional(positional, indentation_level, previous_line, line, next_line, path[-2:] == ".h")
		# remove empty lines in function after variable block
		if line.strip() == "" and positional["function"] and not positional["line_after_variable_block"]:
			continue
		if positional["function_definition"] and previous_line != "":
			lines_corrected.append("")
			previous_line = ""
		line = remove_invalid_tabs(line, positional)
		if indentation_level != 0 and line != "" and not positional["enum"]:
			if (keyword := [key for key in ["if", "while", "else if", "for", "else"] if line[:len(key)] == key]) == []:
				if line != "{" and line != "}":
					if line[-1:] != ";":
						line = line + ";"
		line = check_right_position_of_asterix(line, positional)
		line = add_valid_tabs(index, line, lines, positional, header_prototype_indents, path, indentation_level)
		line = check_spaces_after_keywords(line)
		if not positional["include"]:
			line = check_spaces_around_operators(line)



		# adjust macro indent
		if path[-2:] == ".h"  and len(line) >= 2 and line[:1] == "#":
			directive = line[1:].strip().split(" ", 1)[0]
			if directive == "endif":
				header_define_indent -= 1
			line = "#" + " " * header_define_indent + line[1:].strip()
			if directive == "ifndef" or directive == "ifdef":
				header_define_indent += 1
		
		lines_corrected = append_to_corrected_lines(line, lines_corrected, indentation_level, next_line)
		if positional["variable_block"] and positional["function"] and (next_line != "" \
									  and (find_outside_quotes("=", next_line) != -1 \
									  or find_outside_quotes("(", next_line) != -1 \
										or find_outside_quotes("}", next_line) != -1)):
			lines_corrected.append("")
		
		previous_line = line
	
	return lines_corrected
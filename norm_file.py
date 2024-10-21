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

		"function": False,
		"function_definition": False,
		"variable_block": False,
		
		"one_line_counter": 0
		
	}
	return positional

def split_line_if_has_wrapping_curly_brackets(index, line, lines, in_typedef):
	#todo: find curly brackets after curly brackets in function def or similar, by using while loop over chars
	if ((first_curly := find_outside("{", line, FIND_OUTSIDE_QUOTES))) != -1 \
		and not ((first_curly_closed := find_outside("}", line, FIND_OUTSIDE_QUOTES)) != -1 and \
		first_curly_closed < first_curly):
		if get_markers_count(first_curly, line, FIND_OPEN_ROUND_BRACKETS)[("(", ")")] == 0:
			if line != "{" and line[:-1] != ";":
				line = line.split("{", 1)
				lines.insert(index + 1, "{")
				if (line[1] != ""):
					lines.insert(index + 2, line[1]).strip()
				line = line[0].strip()
				
	if ((first_curly := find_outside("}", line, FIND_OUTSIDE_QUOTES))) != -1:
		if get_markers_count(first_curly, line, FIND_OPEN_ROUND_BRACKETS)[("(", ")")] == 0:
			if line != "}" and line[:-1] != ";" and not in_typedef:
				line = line.split("}", 1)
				lines.insert(index + 1, "}")
				if (line[1] != ""):
					lines.insert(index + 2, line[1]).strip()
				line = line[0].strip()
	return line

def get_indentation_level_for_current_line(previous_line, markers_count, current_line, positional):
	if markers_count != None:
		markers_count[('"', '"', NO_OTHERS_INSIDE)] = 0
		markers_count[("'", "'", NO_OTHERS_INSIDE)] = 0
	markers_count = get_markers_count(None, previous_line, FIND_OPEN_CURLY_BRACKETS, markers_count)
	indentation_level = markers_count[("{", "}")]
	if current_line == "}" or (positional["typedef"] and current_line[:1] == "}"):
			indentation_level -= 1
	indentation_level += positional["one_line_counter"]
	return markers_count, indentation_level

def update_positional(positional, indentation_level, previous_line, current_line, next_line):
	if indentation_level == 0 and previous_line is not None and len(previous_line) > 0 and previous_line == "}":
		positional["function"] = False
		positional["function_definition"] = False
		positional["variable_block"] = False
		positional["struct"] = False
		positional["enum"] = False
		positional["union"] = False
		positional["typedef"] = False

	if positional["function_definition"]:
		positional["function_definition"] = False

	if indentation_level == 0 and next_line is not None and next_line == "{":
		if current_line.find("typedef ") != -1 or current_line.find("struct ") != -1 \
			or current_line.find("union ") != -1 or current_line.find("enum ") != -1:
			if current_line.find("typedef ") != -1:
				positional["typedef"] = True
			if current_line.find("struct ") != -1:
				positional["struct"] = True
			elif current_line.find("enum ") != -1:
				positional["enum"] = True
			elif current_line.find("union ") != -1:
				positional["union"] = True
		else:
			positional["function"] = True
			positional["function_definition"] = True

	if (positional["function"] or positional["struct"] or positional["union"]) \
		and indentation_level == 1 and previous_line == "{":
		positional["variable_block"] = True
	if positional["variable_block"] and (current_line == "" \
									  or find_outside_quotes("=", current_line) != -1 \
									  or find_outside_quotes("(", current_line) != -1 \
										or find_outside_quotes("}", current_line) != -1):
		positional["variable_block"] = False
	
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
		if positional["variable_block"] or positional["typedef"] or positional["function_definition"]:
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
	# check for space after break keyword
	if (keyword := [key for key in ["break"] if current_line[:len(key) + 1] == key + ";"]) != []:
		keyword = keyword[0]
		current_line = current_line(keyword, 1)
		current_line = (keyword + " ").join(current_line)
	return current_line

def add_valid_tabs(line_index, line, lines, positional, header_prototype_indents, path, indent_level):
	if positional["function_definition"]:
		line = set_indent_of_function_declr(line)

	if positional["variable_block"]:
		indent = get_indent_of_variable_block(line_index, lines)
		line = set_indent_of_var_declr(line, indent)

	if path[-2:] == ".h" and indent_level == 0 and line[-1:] == ";" and find_outside_quotes("(", line) != -1:
		line = set_indent_of_function_declr(line, header_prototype_indents)

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


	for index, line in enumerate(lines):
		# do not manipulate lines with comments
		if sum((has_comment := check_for_comments(line, has_comment)).values()) > 0:
			lines_corrected.append(line)
			continue
		line = split_line_if_has_wrapping_curly_brackets(index, line, lines, positional["typedef"])

		markers_count, indentation_level = get_indentation_level_for_current_line(previous_line, markers_count, line, positional)
		if index < len(lines) - 1:
			next_line = lines[index + 1].strip()
		else:
			next_line = None
		
		positional = update_positional(positional, indentation_level, previous_line, line, next_line)
		line = remove_invalid_tabs(line, positional)
		line = add_valid_tabs(index, line, lines, positional, header_prototype_indents, path, indentation_level)

		line = check_spaces_after_keywords(line)

		lines_corrected = append_to_corrected_lines(line, lines_corrected, indentation_level, next_line)
		previous_line = line
	
	return lines_corrected
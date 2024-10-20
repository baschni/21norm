
from file_and_multi_lines import read_file_and_split_into_stripped_lines, join_multi_lines, split_multi_lines
from brackets_quotes_comments import check_for_comments
from header import extract_header

def norm(path, errors):
	original_file, list_of_lines = read_file_and_split_into_stripped_lines(path)
	original_header, lines_after_header = extract_header(list_of_lines)
	no_multi_lines = join_multi_lines(lines_after_header)
	normed_lines = correct_lines_to_norm(lines_after_header)
	with_multi_lines = split_multi_lines(normed_lines)
	# check_and_if_ok_write_file

def correct_lines_to_norm(lines):
	lines_corrected = []
	has_comment = None

	for line in lines:
		if has_comment := check_for_comments(line, has_comment):
			continue



def norm_file(path, errors_before):

	

	# extract header


	if path[:-2] == ".h":
		header_prototype_indents = get_indent_of_prototypes_in_h_file(file)
	else:
		header_prototype_indents = 0
		
	previous = None
	next_line = None
	lines = len(file)
	brackets = 0
	in_multi_line_comment = False
	change_multi_line_comment = False
	in_function = False
	line_of_function_definition = False
	in_variable_block = False
	#after_variable_block = False
	in_enum = False
	in_struct = False
	in_union = False
	in_typedef = False
	in_one_line_block = False
	one_line_counter = 0
	in_multi_line = False
	multi_line_index = None
	multi_lines = []

	# check all other problems
	for index, current in enumerate(file):
		# remove all white space from end of line

		#check for multiline comment and jump all comment lines
		if previous is not None and line[-2:] == "*/":
			change_multi_line_comment = True
		if line[:2] == "/*":
			in_multi_line_comment = True
		if change_multi_line_comment:
			change_multi_line_comment = False
			in_multi_line_comment = True
		if in_multi_line_comment:
			continue

		if line[-1:] == "\\" or (previous is not None and previous != "" and previous[-1:] == "\\"):
			in_multi_line = True
			previous, next_line, multi_lines, multi_line_index = get_multi_lines(index, file)
		else:
			in_multi_line = False
			mult_line_index = None


		
		# check that all curly braces are on their own line
		# todo: how to keep track of open brackets for a multiline with \ ?
		if (first_curly := line.find("{")) != -1:
			if not in_multi_line and get_open_brackets(line, first_curly) == 0 and line.strip() != "{" and line[:-1] != ";":
				line = line.split("{", 1)
				file.insert(index + 1, "\t" * brackets + "{")
				if (line[1] != ""):
					file.insert(index + 2, "\t" * (brackets + 1) + line[1])
				line = line[0]
		if (first_curly := line.find("}")) != -1:
			if  not in_multi_line and get_open_brackets(line, first_curly) == 0 and line.strip() != "}"  and line[:-1] != ";" and not in_typedef:
				line = line.split("}", 1)
				file.insert(index + 1, "\t" * max(brackets - 1, 0) + "}")
				if (line[1] != ""):
					file.insert(index + 2, "\t" * max(brackets - 1, 0) + line[1])
				line = line[0]



		if brackets == 0 and previous is not None and len(previous) > 0 and previous.strip() == "}":
			in_function = False
			line_of_function_definition = False
			in_struct = False
			in_enum = False
			in_union = False
			in_typedef = False

		if not in_multi_line:
			if index < lines - 1:
				next_line = file[index + 1].rstrip()
			else:
				next_line = None
		
		# todo: handle if function definition is spread on multiple lines
		if line_of_function_definition == True:
			line_of_function_definition = False

		# check for functions, struct, unions, enums ...
		if brackets == 0 and next_line is not None and next_line.strip() == "{":
			if line.find("typedef ") != -1 or line.find("struct ") != -1 or line.find("union ") != -1 or line.find("enum ") != -1:
				if line.find("typedef ") != -1:
					in_typedef = True
				if line.find("struct ") != -1:
					in_struct = True
				elif line.find("enum ") != -1:
					in_enum = True
				elif line.find("union ") != -1:
					in_union = True
			else:
				in_function = True
				line_of_function_definition = True
		if line_of_function_definition:
			lsplit = line.split("(", 1)
			first = lsplit[0]
			inv = first[::-1]
			c = ""
			for i, c in enumerate(inv):
				if (c.isalnum() or c == "_"):
					pass
				elif (c == "*"):
					break
				else:
					break
			if c == " " or (c == "*" and (i + 1) < len(inv) and inv[i + 1] == " "):
				fsplit = first.rsplit(" ", 1)
				line = fsplit[0] + "\t" + fsplit[1] + "(" + lsplit[1]
				
		if (in_function or in_struct or in_union) and brackets == 1 and previous.strip() == "{":
			in_variable_block = True
		# todo: find right amount of indentation of block
		if in_variable_block:
			if line[-1:] == ";":
				inv = line[:-1][::-1]
				print(line)
				print (inv)
				c = ""
				for i, c in enumerate(inv):
					if (c.isalnum() or c == "_"):
						pass
					elif (c == "*"):
						break
					else:
						break
				print(c, c == " ", c == "*")
				if c == " " or (c == "*" and (i + 1) < len(inv) and inv[i + 1] == " "):
					fsplit = line.rsplit(" ", 1)
					line = fsplit[0] + "\t" + fsplit[1]
					print("here!", line)
		if in_variable_block and (line.strip() == "" or line.find("=") != -1 or line.find("(") != -1 or line.find("}") != -1):
			in_variable_block = False

		# remove all tabs on normal lines that appear after indent
		line_new = []
		for c in line:
			if in_variable_block or in_typedef or line_of_function_definition:
				line_new.append(c)
			elif c == "\t":
				line_new.append(" ")
			else:
				line_new.append(c)
		line = "".join(line_new)

		if line != "":
			line = "\t" * brackets + line

		# increase or decrease function definition
		one_line = line if not in_multi_line else multi_lines[0]
		if in_one_line_block:
			if not in_multi_line or [key for key in ["if (", "while (", "if(", "while(", "else if ", "if ", "else", "while "] if one_line.lstrip()[:len(key)] == key] == []:
				in_one_line_block = False
				brackets = max(brackets - one_line_counter, 0)
				one_line_counter = 0
		if [key for key in ["if (", "while (", "if(", "while(", "else if ", "if ", "else", "while "] if one_line.lstrip()[:len(key)] == key] != []:
			if next_line is not None and next_line.strip() != "{":
				in_one_line_block = True
				brackets += 1
				one_line_counter += 1
		elif line.strip() == "{":
			brackets += 1
		if next_line is not None and len(next_line.strip()) > 0 and next_line.strip()[0] == "}":
			brackets = max(brackets - 1, 0)

		# if next.strip() == "{"


		# remove consecutive newlines
		if line == "" and (previous == "" or previous == "\n"):
			line = "\n"

		line_new = []
		ppc = ""
		pc = ""
		nc = ""
		# remove consecutive spaces
		for i, c in enumerate(line):
			if c == '"':
				if quotes:
					quotes = False
				else:
					quotes = True
			if quotes:
				continue
			
			if i < len(line) - 1:
				nc = line[i + 1]
			else:
				nc = ""
			if c == " " and pc == " ":
				pass
			#elif c == "*" and pc != " ":
			# todo: check for function prototype, where tab is needed in front of "*"
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
				if nc != "=" and nc != " ":
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
			pc = c
		line = "".join(line_new)
		
		
		#check all but last
		if next_line is not None:
			# remove whitespace at beginning of block
			if previous == "{":
				if line == "":
					line = "\n"

			#check for brackets around return
			# check for space after keyword
			if (keyword := [key for key in ["if", "while", "else if", "return"] if line.lstrip()[:len(key) + 1] == key + "("]) != []:
				keyword = keyword[0]
				line = line.split(keyword, 1)
				line = (keyword + " ").join(line)
			# check for return parentheses
			ret_len = len("return ")
			if line.lstrip()[:ret_len] == "return " and line.lstrip()[:ret_len + 1] != "return ;":
				if line.lstrip()[ret_len] != "(":
					ret_index = line.find("return ")
					line = line[:ret_index + ret_len] + "(" + line[ret_index + ret_len:-1] + ")" + line[-1]
			# check for space after break keyword
			if (keyword := [key for key in ["break"] if line.lstrip()[:len(key) + 1] == key + ";"]) != []:
				keyword = keyword[0]
				line = line.split(keyword, 1)
				line = (keyword + " ").join(line)
		# check last line
		if next_line is None:
			if line.strip() == "}":
				file.append("")

		previous = current
		file[index] = line
	
	file = [line for line in file if line != "\n"]
	file = "\n".join(file)
	if len(file) != 0 and file[0] != "\n":
		file = "\n" + file
	if header + file != orig or [error for error in errors_before[path] if error["error_code"] == "INVALID_HEADER"] != []:
		header = create_header(path, USER, EMAIL)
		tmp_file = "." + NAME + ".tmp" + path[-2:]
		with open(tmp_file, "w", encoding="utf-8") as f:
			f.write(header + file)
		error_count = error_count_for_file(tmp_file)
		if error_count != -1 and not error_count >= len(errors_before[path]):
			with open(path, "w", encoding="utf-8") as f:
				f.write(header + file)
		else:
			print(path + ": Error: " + NAME + " could not parse file. skipping...")
		#os.remove("." + NAME + ".tmp")
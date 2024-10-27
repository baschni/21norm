from brackets_quotes_comments import find_outside_quotes

def get_indent_of_prototypes_in_h_file(file):
	brackets = 0
	indents = [0]
	for line in file:
		if find_outside_quotes("{", line) != -1:
			brackets += 1
		elif find_outside_quotes("}", line) != -1:
			brackets = max(0, brackets - 1)
		
		if brackets == 0 and line.strip()[-1:] == ";" and line.strip()[:len("typedef")] != "typedef":
			indents.append(get_indent_of_function_declr(line))
	return max(indents)

def get_indent_of_variable_block(line_index, lines):
	block =[]
	index = line_index - 1
	while index > 0 and lines[index].strip() != "{":
		block.append(lines[index])
		index -= 1
	block.append(lines[line_index])
	index = line_index + 1
	flen = len(lines)
	cline = lines[index]
	while index < flen and (cline.strip() != "" and cline.find("}") == -1 and cline.find("(") == -1 and cline.find("=") == -1):
		block.append(lines[index])
		index  += 1
		if index < flen:
			cline = lines[index]
	indents = []
	for line in block:
		indents.append(get_indent_of_var_declr(line))
	return max(indents)

def set_indent_of_function_declr(line, indent = 0):
	split = line.split("(", 1)
	print("splitting", indent, line)
	indented = set_indent_of_var_declr(split[0], indent)
	return indented + "(" + split[1]

def get_indent_of_function_declr(line):
	first = line.strip().split("(", 1)[0]
	return get_indent_of_var_declr(first)

def get_indent_of_var_declr(line):
	line_len = len(line)
	index_second = -1
	len_first = -1
	square_brackets = 0
	for index, char in enumerate(reversed(line)):
		if char == ']':
			square_brackets += 1
		elif char == '[':
			square_brackets -= 1
		elif not char.isspace() and index_second == -1:
			pass
		elif not square_brackets and char.isspace() and index_second == -1:
			index_second = line_len - index
		elif not char.isspace() and index_second != -1:
			len_first = line_len - index
			break
	if len_first == -1 or index_second == 1:
		return -1
	indent = int(len_first / 4) + 1
	return indent


def set_indent_of_var_declr(line, indent):
	line_len = len(line)
	index_second = -1
	len_first = -1
	square_brackets = 0
	for index, char in enumerate(reversed(line)):
		if char == ']':
			square_brackets += 1
		elif char == '[':
			square_brackets -= 1
		elif not char.isspace() and index_second == -1:
			pass
		elif not square_brackets and char.isspace() and index_second == -1:
			index_second = line_len - index
		elif not char.isspace() and index_second != -1:
			len_first = line_len - index
			break
	if len_first == -1 or index_second == 1:
		return line
	line = line[:len_first] + "\t" * max((indent - int(len_first / 4)), 1) + line[index_second:]
	return (line)

def get_indent_of_prototypes_in_h_file(file):
	brackets = 0
	indents = []
	for line in file:
		for c in line:
			if c == "{":
				brackets += 1
			elif c == "}":
				brackets = max(0, brackets - 1)
		
		if brackets == 0 and line.strip()[-1:] == ";":
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
	while index < flen and (cline.strip() != "" or cline.find("}") != -1 or cline.find("(") != -1 or cline.find("=") != -1):
		block.append(lines[index])
		index  += 1
		if index < flen:
			cline = lines[index]
	indents = []
	for line in block:
		indents.append(get_indent_of_var_declr(line))
	return max(indents)

def set_indent_of_function_declr(line, indent):
	split = line.split("(", 1)
	indented = set_indent_of_var_declr(split[0] + ";")
	return indented[:-1] + "(" + split[1]

def get_indent_of_function_declr(line):
	first = line.strip().split("(", 1)[0]
	return get_indent_of_function_declr(first + ";")

def get_indent_of_var_declr(line):
	pass

def set_indent_of_var_declr(line):
	pass
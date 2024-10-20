
def error_count_for_file(file):
	errors = 0
	try:
		output = check_output([NORMINETTE_EXECUTABLE, file], )
	except CalledProcessError as err:
		output = err.output
	output = output.decode("utf-8").split("\n")
	current_file = None
	for line in output:
		if line[-5:] == ": OK!" or line == "":
			next
		elif line[-8:] == ": Error!":
			current_file = line[:-8]
		else:
			if line.find(ERROR_UNRECOGNIZED_TOKEN) != -1 or line.find(ERROR_UNRECOGNIZED_LINE) != -1:
				return (-1)
			errors += 1
	return errors

def get_left_white_space(line):
	tabs = 0
	non_tabs = 0
	for c in line:
		if c == "\t":
			tabs += 1
		elif c.isspace():
			non_tabs += 1
		else:
			return (tabs, non_tabs)
	return (tabs, non_tabs)




def get_open_brackets(line, index):
	brackets = 0
	for c in line[:index]:
		if c == "(":
			brackets += 1
		elif c == ")":
			if brackets > 0:
				brackets -= 1
	return (brackets)

def get_multi_lines(index, lines):
	previous = None
	next_line = None
	multi_index = 0
	mlines = [lines[index]]
	i = index - 1
	while i > 0 and lines[i][-1:] == "\\":
		multi_index += 1
		mlines.insert(0, lines[i])
		i -= 1
	if i > 0:
		previous = lines[i]
	i = index + 1
	le = len(lines)
	if lines[index].rstrip()[-1:] == "\\":
		while i < le and lines[i].rstrip()[-1:] == "\\":
			mlines.append(lines[i].rstrip())
			i += 1
		if i < le:
			mlines.append(lines[i].rstrip())
			i += 1
	if i < le:
		next_line = lines[i].rstrip()
	return (previous, next_line, mlines, multi_index)
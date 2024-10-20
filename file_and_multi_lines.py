from brackets_quotes_comments import find_outside, NO_OTHERS_INSIDE

def read_file_and_split_into_stripped_lines(path: str):
	"""	read file, split into lines and remove empty lines
		at start and end
	"""
	with open(path, "r", encoding="utf-8") as f:
		orig = f.read()
	file = orig.split("\n")

	for index, line in enumerate(file):
		file[index] = line.strip()

	for index, line in enumerate(file):
		if line != "":
			break ;
		del file[index]
	
	for index, line in enumerate(reversed(file)):
		if line != "":
			break ;
		del file[index]
	
	return orig, file

def join_multi_lines(broken_lines):
	joined_lines = []
	joined_line = ""
	previous_was_broken = False
	has_comment = None
	for line in broken_lines:
		has_comment = check_for_comments(line, has_comment)
		if has_comment["//"] or has_comment["/*"]:
			continue
		if line[:-1] == "\\":
			joined_line += line
			previous_was_broken = True
		else:
			if previous_was_broken:
				joined_lines.append(joined_line + line)
				joined_line = ""
			else:
				joined_lines.append(line)
			previous_was_broken = False

def split_multi_lines(joined_lines):
	broken_lines = []
	for line in joined_lines:
		while (index := find_outside(line, "\\", \
							   [('"', '"', NO_OTHERS_INSIDE), ("'", "'", NO_OTHERS_INSIDE)])) != -1:
			broken_lines.append(line[:index + 1])
			line = line[index + 2:]
		broken_lines.append(line)
	return (broken_lines)

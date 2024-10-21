from typing import List
from config import NAME, USER, EMAIL
from brackets_quotes_comments import find_outside, NO_OTHERS_INSIDE, check_for_comments, get_markers_count
from parse_norminette import error_codes_for_file
from header import create_header
import os

def read_file_and_split_into_stripped_lines(path: str):
	"""	read file, split into lines and remove empty lines
		at start and end, remove consecutive new lines
	"""
	with open(path, "r", encoding="utf-8") as f:
		orig = f.read()
	file = orig.split("\n")

	has_comment = None
	for index, line in enumerate(file):
		if not sum((has_comment := check_for_comments(line, has_comment)).values()) > 0:
			file[index] = line.strip()

	for index, line in enumerate(file):
		if line != "":
			break ;
		del file[index]
	
	len_file = len(file)
	for index, line in enumerate(reversed(file)):
		if line != "":
			break ;
		del file[len_file - 1 - index]

	start_len = len(file)
	next_line = None
	for index, line in enumerate(reversed(file)):
		
		if line == "" and next_line == "":
			del file[start_len - index]
		elif line == "{" and next_line == "":
			del file[start_len - index]
		next_line = line

	return orig, file

def remove_consecutive_spaces(line):
	previous_char = ""
	line_new = []
	for index, char in enumerate(line):
		inside_quotes = get_markers_count(line, char, [('"', '"', NO_OTHERS_INSIDE), ("'", "'", NO_OTHERS_INSIDE)])
		if sum(inside_quotes.values()) == 0 and previous_char.isspace() and char.isspace():
			pass
		else:
			line_new.append(char)
		previous_char = char
	return ("".join(line_new))

def join_multi_lines(broken_lines) -> List[str]:
	joined_lines = []
	joined_line = ""
	previous_was_broken = False
	has_comment = None
	for line in broken_lines:
		has_comment = check_for_comments(line, has_comment)
		if has_comment["//"] or has_comment["/*"]:
			joined_lines.append(line)
			continue
		if line[-1:] == "\\":
			joined_line += line
			previous_was_broken = True
		else:
			if previous_was_broken:
				joined_lines.append(remove_consecutive_spaces(joined_line + line))
				joined_line = ""
				previous_was_broken = False
			else:
				joined_lines.append(remove_consecutive_spaces(line))
	return (joined_lines)

def first_non_white_space(line):
	for index, char in enumerate(line):
		if not char.isspace():
			return index
	return -1

def split_multi_lines(joined_lines):
	broken_lines = []
	for line in joined_lines:
		while (index := find_outside("\\", line, \
							   [('"', '"', NO_OTHERS_INSIDE), ("'", "'", NO_OTHERS_INSIDE)])) != -1:
			first_line = line[:index + 1]
			broken_lines.append(first_line)
			first_char = first_non_white_space(first_line)
			if first_char != -1:
				line = first_line[:first_char] + line[index + 1:]
			else:
				lien = line[index + 1:]
		broken_lines.append(line)
	return (broken_lines)

def get_include_guard_name(path: str):
	name = os.path.basename(path)
	new = []
	for c in name:
		if c.isalpha():
			new.append(c.capitalize())
		elif c.isnumeric():
			new.append(c)
		else:
			new.append("_")
	return ("".join(new))

def check_include_guards(new_file: str, path: str):
	if path[-2:] != ".h":
		return new_file
	file = new_file.split("\n")

	for index, line in enumerate(file):
		if line != "":
			break ;
		del file[index]

	for index, line in enumerate(reversed(file)):
		if line != "":
			break ;
		del file[len(file) - 1 - index]
	
	guard_name = get_include_guard_name(path)

	if file[0][:len("#ifndef ")] == "#ifndef " and file[1][:len("# define ")] == "# define " and (file[-1] == "#endif" or file[-1] == "# endif"):
		file[0] = f"#ifndef {guard_name}"
		file[1] = f"# define {guard_name}"
		file[-1] = "#endif"
		return ("\n" + "\n".join(file))
	else:
		return "\n" + f"#ifndef {guard_name}\n" + f"# define {guard_name}\n" + new_file + "\n\n#endif"


def check_and_if_ok_write_file(path, normed_lines, errors_before, \
							   orig_header, orig_file, orig_creation_date, orig_creation_user):
	"""The new file is prepared by joining the normed lines togehter. Some checks are then
	made:
	(1) did the norming have any effect (are the new_lines + the original header
	the same as the old file?), then the file needs not be changed.
	(2) was the header missing before? than (1) will still be true, but the new file
	will be written with a new header instead of any norming
	"""
	new_file = [line for line in normed_lines if line != "\n"]
	new_file = "\n".join(new_file)
	if len(new_file) != 0 and new_file[0] != "\n":
		new_file = "\n" + new_file

	error_codes_before = [error["error_code"] for error in errors_before[path]]
	if orig_header + new_file != orig_file or "INVALID_HEADER" in error_codes_before:
		tmp_file = "." + NAME + ".tmp" + path[-2:]
		with open(tmp_file, "w", encoding="utf-8") as f:
			f.write(create_header(tmp_file, USER, EMAIL, orig_creation_date, orig_creation_user) + check_include_guards(new_file, tmp_file))
		error_codes = error_codes_for_file(tmp_file)
		#print(error_codes, len(error_codes), len(errors_before[path]), [code for code in error_codes if code not in error_codes_before])
		if len(error_codes) == len(errors_before[path]):
			return
		if not len(error_codes) > len(errors_before[path]) \
			and len([code for code in error_codes if code not in error_codes_before]) == 0:
			header = create_header(path, USER, EMAIL, orig_creation_date, orig_creation_user)
			with open(path, "w", encoding="utf-8") as f:
				f.write(header + check_include_guards(new_file, path))
		else:
			print(path + ": Error: " + NAME + " could not parse file. skipping...")
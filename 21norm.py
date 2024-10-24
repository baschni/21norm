#!python3

# todo:
# make normer work with missing semicolon in the end
# add line wrapping in variable block of doxygen comments
# NEWLINE_PRECEDES_FUNC        Functions must be separated by a newline
# output no line break before final line if no norminette or 21norm parsing errors occured

import sys
import os

from file_and_multi_lines import read_file_and_split_into_stripped_lines, \
	join_multi_lines, split_multi_lines, check_and_if_ok_write_file
from header import extract_header
from norm_file import correct_lines_to_norm
from parse_norminette import get_errors_from_norminette
from config import NAME
from doxygen import break_doxygen_comments

def recursive_c_h_file_search(folder):
	ls = os.listdir(folder)
	files = []
	for file in ls:
		if file[:len("." + NAME + ".tmp")] == "." + NAME + ".tmp":
			continue
		if os.path.isdir(os.path.join(folder, file)) and not os.path.islink(os.path.join(folder, file)):
			files = [*files, *recursive_c_h_file_search(os.path.join(folder, file))]
		elif(file[-2:] == ".c" or file[-2:] == ".h"):
			file = os.path.join(folder, file)
			if file[:2] == "./":
				file = file[2:]
			files.append(file)
	return files

def norm_file(path, errors):
	original_file, list_of_lines = read_file_and_split_into_stripped_lines(path)
	original_header, lines_after_header, orig_creation_date, orig_creation_user = extract_header(list_of_lines)
	no_multi_lines = join_multi_lines(lines_after_header)
	normed_lines = correct_lines_to_norm(no_multi_lines, path)
	normed_lines2 = break_doxygen_comments(normed_lines)
	with_multi_lines = split_multi_lines(normed_lines2)
	check_and_if_ok_write_file(path, with_multi_lines, errors, \
							original_header, original_file, orig_creation_date, orig_creation_user)

if __name__ == "__main__":
	files = sys.argv[1:]

	if files == []:
		files = recursive_c_h_file_search(".")
	if files == []:
		exit()
	files_orig = files

	errors_before, skipped = get_errors_from_norminette(files)
	max_indent = 0
	for file in skipped:
		max_indent = max(max_indent, int(len("skipped: " + file) / 4) + 2)
	for file, error in skipped.items():
		print("skipped " + file + ":" + " " * (max_indent * 4 - len("skipped: " + file)) + error)
	for file in files:
		if file in errors_before:
			norm_file(file, errors_before)

	errors_after, _ = get_errors_from_norminette(files_orig)
	int_err_before =  sum(len(val) for val in errors_before.values())
	int_err_after = sum(len(val) for val in errors_after.values())
	if int_err_before != 0 or len(skipped) != 0:
		print(f"\nnormer removed {int_err_before - int_err_after} of {int_err_before} norm errors in {len(errors_before)} files" )
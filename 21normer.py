#!python

# todo:
# check tab before function definition
# check tab in variable block
# check newline after variable block
# check tab after enum union struct typedef
# check include guards for headers
# check indent in preprocesser statements after include guard
# remove tab if not on beginning of line, in variable block or in typedef!
# problem if lines are broken by \ ?
# bug: some problems are removed after second run of normer
# idea: only really change something if norminette gave the line of error of the change?
# todo: check if after run no new error codes are added to norminette, if yes, do not modify the file
# bug: problem with indentation with if on multilines
# todo: when rechecking with norminette on a temp file, for headers the wrong protection name is detected
# prototypes in c files as well as h files

import sys
import os

from subprocess import check_output, CalledProcessError
from file_and_multi_lines import read_file_and_split_into_stripped_lines, \
	join_multi_lines, split_multi_lines, check_and_if_ok_write_file
from header import extract_header
from norm_file import correct_lines_to_norm
from parse_norminette import get_errors_from_norminette

def recursive_c_h_file_search(folder):
	ls = os.listdir(folder)
	files = []
	for file in ls:
		if os.path.isdir(file) and not os.path.islink(file):
			files = [*files, *recursive_c_h_file_search(os.path.join(folder, file))]
		elif(file[-2:] == ".c" or file[-2] == ".h"):
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
	with_multi_lines = split_multi_lines(normed_lines)
	check_and_if_ok_write_file(path, with_multi_lines, errors, \
							original_header, original_file, orig_creation_date, orig_creation_user)

if __name__ == "__main__":
	files = sys.argv[1:]

	if files == []:
		files = recursive_c_h_file_search(".")

	errors_before = get_errors_from_norminette(files)
	for file in files:
		if file in errors_before:
			norm_file(file, errors_before)
	errors_after = get_errors_from_norminette(files)
	int_err_before =  sum(len(val) for val in errors_before.values())
	int_err_after = sum(len(val) for val in errors_after.values())
	print(f"normer removed {int_err_before - int_err_after} of {int_err_before} violations of the norm!")
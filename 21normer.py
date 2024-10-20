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



import sys
import os

from subprocess import check_output, CalledProcessError


ERROR_UNRECOGNIZED_TOKEN = "Error: Unrecognized token"
ERROR_UNRECOGNIZED_LINE = "Error: Unrecognized line"



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


def get_errors_from_norminette(files):
	errors = {}
	try:
		output = check_output([NORMINETTE_EXECUTABLE, *files], )
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
				del files[current_file]
				print(current_file + ": Error: norminette could not parse file. skipping...")
				continue
			front, detail = line.split("):")
			code, position = front.strip().split("(")
			code = code[7:]
			position = position.split(",")
			line_number = int(position[0].split(":")[1].strip())
			column_number = int(position[1].split(":")[1].strip())
			if not current_file in errors:
				errors[current_file] = []
			errors[current_file].append({"error_code": code.strip(), "error_msg": detail.strip(), "line": line_number, "column": column_number})
	return errors



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
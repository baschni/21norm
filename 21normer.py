#!python

#todo:
#check tab before function definition
#check tab in variable block
#check newline after variable block
#check tab after enum union struct typedef
#check include guards for headers

import sys
import os
import datetime
from subprocess import check_output, CalledProcessError

NORMINETTE_EXECUTABLE = "norminette"
NAME = "baschnit"
EMAIL = "baschnit@student.42lausanne.ch"
HEADER_ASCII = """

        :::      ::::::::   
      :+:      :+:    :+:   
    +:+ +:+         +:+     
  +#+  +:+       +#+        
+#+#+#+#+#+   +#+           
     #+#    #+#             
    ###   ########.fr       
""".split("\n")
SPACE_BEFORE_ASCII = 48
SPACE_BEFORE_CONTENT = 3
HEADER_LINES = 11
HEADER_WIDTH = 80
def create_header(filepath, name, email):
	header = ""
	i = 0
	for i in range(0, HEADER_LINES):
		if i == 0 or i == HEADER_LINES - 1:
			header += "/* " + "*" * (HEADER_WIDTH - 6)  + " */\n"
		elif i not in range(2,9):
			header += "/*" + " " * (SPACE_BEFORE_ASCII + len(HEADER_ASCII[2])) + "*/\n"
		else:
			content = ""
			if i == 3:
				content = os.path.basename(file)
			elif i == 5:
				content = "By: " + name + " <" + email + ">"
			elif i == 7:
				stamp = datetime.datetime.now().strftime("%Y/%M/%d %H:%M:%S")
				content = "Created: " + stamp + " by " + name
			elif i == 8:
				content = "Updated: " + stamp + " by " + name
			space_after_content = SPACE_BEFORE_ASCII - SPACE_BEFORE_CONTENT - len(content)
			header += "/*" + " " * SPACE_BEFORE_CONTENT + content + " " * space_after_content + HEADER_ASCII[i] + "*/\n"
	return header

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

def norm_file(path, errors_before):
	with open(path, "r", encoding="utf-8") as f:
		file = f.read()
	file = file.split("\n")

	previous = None
	next = None
	lines = len(file)
	brackets = 0
	in_function = False
	after_variable_block = False
	in_enum = False
	in_struct = False
	in_union = False
	in_typedef = False
	in_one_line_block = False

	# check header
	header = ""
	if [error for error in errors_before[path] if error["error_code"] == "INVALID_HEADER"] != []:
		header = create_header(path, NAME, EMAIL)

	# check all other problems
	for index, current in enumerate(file):
		# remove all white space from end of line
		line = current.strip()
		if line != "":
			line = "\t" * brackets + current.strip()
		# check that there are only tabs as indent
		# lspace = get_left_white_space(line)
		# total_indent = (lspace[0] + int(lspace[1] / 4))
		# if lspace[1] > 0:
		# 	line = "\t" * (lspace[0] + int(lspace[1] / 4)) + line.strip()
		# check that all curly braces are on their own line
		if line.find("{") != -1:
			if line.strip() != "{":
				line = line.split("{", 1)
				file.insert(index + 1, "\t" * total_indent + "{")
				if (line[1] != ""):
					file.insert(index + 2, "\t" * (total_indent + 1) + line[1])
				line = line[0]
		if line.find("}") != -1:
			if line.strip() != "}" and not in_typedef:
				line = line.split("}", 1)
				file.insert(index + 1, "\t" * max(total_indent - 1, 0) + "}")
				if (line[1] != ""):
					file.insert(index + 2, "\t" * total_indent + line[1])
				line = line[0]



		if previous is not None and len(previous) > 0 and previous[0] == "}":
			in_function = False
			in_struct = False
			in_enum = False
			in_union = False
			in_typedef = False

		if index < lines - 1:
			next = file[index + 1].rstrip()
		else:
			next = None

		if in_one_line_block:
			in_one_line_block = False
			brackets -= 1
		if [key for key in ["if (", "while (", "if(", "while(", "else if"] if line.lstrip()[:len(key)] == key] != []:
			if next.strip() != "{":
				in_one_line_block = True
				brackets += 1
		elif line.strip() == "{":
			brackets += 1
		if next is not None and len(next.strip()) > 0 and next.strip()[0] == "}":
			brackets = max(brackets - 1, 0)

		# if next.strip() == "{"


		# remove consecutive newlines
		if line == "" and (previous == "" or previous == "\n"):
			line = "\n"
		
		#check all but last
		if next is not None:
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
			if (keyword := [key for key in ["break"] if line.lstrip()[:len(key) + 1] == key + ";"]) != []:
				keyword = keyword[0]
				line = line.split(keyword, 1)
				line = (keyword + " ").join(line)
		# check last line
		if next is None:
			if line.strip() == "}":
				file.append("")

		previous = current
		file[index] = line
	
	file = [line for line in file if line != "\n"]

	with open(path, "w", encoding="utf-8") as f:
		f.write(header + "\n".join(file))

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
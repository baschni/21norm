#!python
import sys
import os
from subprocess import check_output, CalledProcessError

NORMINETTE_BINARY = "norminette"
NAME = "Bastian Schnitzler"
EMAIL = "baschnit@student.42lausanne.ch"
HEADER_ASCII = """
        :::      ::::::::   
      :+:      :+:    :+:   
    +:+ +:+         +:+     
  +#+  +:+       +#+        
+#+#+#+#+#+   +#+           
     #+#    #+#             
    ###   ########.fr       
"""
SPACE_BEFORE_ASCII = 48
SPACE_BEFORE_CONTENT = 3
HEADER_LINES = 12
HEADER = """
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:25:01 by baschnit          #+#    #+#             */
/*   Updated: 2024/10/18 21:07:07 by baschnit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
"""

def recursive_c_h_file_search(folder):
	ls = os.listdir(folder)
	files = []
	for file in ls:
		if os.path.isdir(file) and not os.path.islink(file):
			files = [*files, *recursive_c_h_file_search(os.path.join(folder, file))]
		elif(file[-2:] == ".c" or file[-2] == ".h"):
			files.append(os.path.join(folder, file))
	return files

def get_errors_from_norminette(files):
	errors = {}
	try:
		output = check_output([NORMINETTE_BINARY, *files], )
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

def norm_file(path):
	with open(path, "r", encoding="utf-8") as f:
		file = f.read()
	file = file.split("\n")

	previous = None
	next = None
	lines = len(file)
	in_function = False;
	in_enum = False;
	in_struct = False;

	# check header

	for index, current in enumerate(file):
		line = current.rstrip()
		if index < lines - 1:
			next = file[index + 1].rstrip()
		else:
			next = None
		#check all but last
		if next is not None:
			# remove whitespace at beginning of function
			# remove consecutive newlines
			if line == "" and next == "":
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
			if line[-1:] == "}":
				line += "\n"

		previous = current
		file[index] = line
	
	file = [line for line in file if line != "\n"]

	with open(path, "w", encoding="utf-8") as f:
		f.write("\n".join(file))

if __name__ == "__main__":
	files = sys.argv[1:]

	if files == []:
		files = recursive_c_h_file_search(".")

	errors_before = get_errors_from_norminette(files)
	for file in files:
		norm_file(file)
	errors_after = get_errors_from_norminette(files)
	int_err_before =  sum(len(val) for val in errors_before.values())
	int_err_after = sum(len(val) for val in errors_after.values())
	print(f"normer removed {int_err_before - int_err_after} of {int_err_before} violations of the norm!")
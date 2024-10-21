from typing import List
from config import NORMINETTE_EXECUTABLE
from subprocess import check_output, CalledProcessError

ERROR_UNRECOGNIZED_TOKEN = "Error: Unrecognized token"
ERROR_UNRECOGNIZED_LINE = "Error: Unrecognized line"
ERROR_NESTED_BRACKETS = "Error: Nested parentheses, braces or brackets are not correctly closed"
ERROR_EXTRA_TOKEN_ENDIF = "Extra tokens at end of #endif directive"
ERROR_STRING_LITERAL_UNTERMINATED = "String literal unterminated"

def get_errors_from_norminette(files: List[str]):
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
			if line.find(ERROR_UNRECOGNIZED_TOKEN) != -1 \
				or line.find(ERROR_NESTED_BRACKETS) != -1 \
				or line.find(ERROR_STRING_LITERAL_UNTERMINATED) != -1 \
				or line.find(ERROR_UNRECOGNIZED_LINE) != -1:
				files.remove(current_file)
				print(current_file + ": Error: norminette could not parse file. skipping...")
				continue
			front, detail = line.split("):")
			code, position = front.strip().split("(")
			code = code[7:].strip()
			position = position.split(",")
			line_number = int(position[0].split(":")[1].strip())
			column_number = int(position[1].split(":")[1].strip())
			if not current_file in errors:
				errors[current_file] = []
			errors[current_file].append({"error_code": code, "error_msg": detail.strip(), "line": line_number, "column": column_number})
	return errors

def error_codes_for_file(file):
	error_codes = []
	try:
		output = check_output([NORMINETTE_EXECUTABLE, file], )
	except CalledProcessError as err:
		output = err.output
	output = output.decode("utf-8").split("\n")
	#current_file = None
	for line in output:
		if line[-5:] == ": OK!" or line == "":
			next
		elif line[-8:] == ": Error!":
			pass
			# current_file = line[:-8]
		else:
			if line.find(ERROR_UNRECOGNIZED_TOKEN) != -1:
				error_codes.append(ERROR_UNRECOGNIZED_TOKEN)
				continue
			if line.find(ERROR_UNRECOGNIZED_LINE) != -1:
				error_codes.append(ERROR_UNRECOGNIZED_LINE)
				continue
			if line.find(ERROR_NESTED_BRACKETS) != -1:
				error_codes.append(ERROR_NESTED_BRACKETS)
				continue
			if line.find(ERROR_EXTRA_TOKEN_ENDIF) != -1:
				error_codes.append(ERROR_EXTRA_TOKEN_ENDIF)
				continue
			if line.find(ERROR_STRING_LITERAL_UNTERMINATED) != -1:
				error_codes.append(ERROR_EXTRA_TOKEN_ENDIF)
				continue
			front, _ = line.split("):")
			code, _ = front.strip().split("(")
			code = code[7:].strip()
			error_codes.append(code)
	return error_codes
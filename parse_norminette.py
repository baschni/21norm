from typing import List
from config import NORMINETTE_EXECUTABLE
from subprocess import check_output, CalledProcessError

ERROR_UNRECOGNIZED_TOKEN = "Error: Unrecognized token line "
ERROR_UNRECOGNIZED_LINE = "Error: Unrecognized line ("
ERROR_STRING_LITERAL_UNTERMINATED = "String literal unterminated detected at line "

ERROR_NESTED_BRACKETS = "Error: Nested parentheses, braces or brackets are not correctly closed"
ERROR_INVALID_PREPROCESSING_DIRECTIVE = "Invalid preprocessing directive"
ERROR_EXTRA_TOKEN_ENDIF = "Extra tokens at end of #endif directive"
ERROR_INCLUDE_FILE_ARGUMENT = "Invalid file argument for #include directive"

ERROR_NO_SUCH_FILE = "no such file or directory"
ERROR_NO_VALID_C_FILE = "is not valid C or C header file"

ERROR_WITH_LINE_INFO = [ERROR_UNRECOGNIZED_LINE, ERROR_UNRECOGNIZED_TOKEN, ERROR_STRING_LITERAL_UNTERMINATED]
ERROR_WITH_LINE_INFO_TO_FIND = [ERROR_NESTED_BRACKETS, ERROR_EXTRA_TOKEN_ENDIF, ERROR_INVALID_PREPROCESSING_DIRECTIVE, ERROR_INCLUDE_FILE_ARGUMENT]
ERROR_WITHOUT_LINE_INFO = [ERROR_NO_VALID_C_FILE, ERROR_NO_SUCH_FILE]

def find_from_list(line: str, needles: List[str]):
	for needle in needles:
		if (res := line.find(needle)) != -1:
			return needle
	return ""

def get_errors_from_norminette(files: List[str]):
	errors = {}
	skipped = {}
	if files == []:
		return errors
	try:
		output = check_output([NORMINETTE_EXECUTABLE, *files], )
	except CalledProcessError as err:
		output = err.output
	output = output.decode("utf-8").split("\n")
	current_file = None

	for line in output:
		if line[-5:] == ": OK!" or line == "":
			continue
		elif line[-8:] == ": Error!":
			current_file = line[:-8]
		elif (error := find_from_list(line, ERROR_WITHOUT_LINE_INFO)) != "":
			line = line.replace("Error:", "").strip()
			current_file = line[:line.find(" ")].strip().replace("'", "")
			skipped[current_file] = error.strip()
		elif (error := find_from_list(line, ERROR_WITH_LINE_INFO)) != "":
			skipped[current_file] = error[:-1].replace("Error: ", "").strip()
		elif (error := find_from_list(line, ERROR_WITH_LINE_INFO_TO_FIND)) != "":
			skipped[current_file] = error.replace("Error: ", "").strip()
		else:
			front, detail = line.split("):")
			code, position = front.strip().split("(")
			code = code[7:].strip()
			position = position.split(",")
			line_number = int(position[0].split(":")[1].strip())
			column_number = int(position[1].split(":")[1].strip())
			if not current_file in errors:
				errors[current_file] = []
			errors[current_file].append({"error_code": code, "error_msg": detail.strip(), "line": line_number, "column": column_number})
	return errors, skipped

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
	
	error_codes = [code for code in error_codes if code != "LINE_TOO_LONG"]
	return error_codes
#!python3
MAX_LINE_LENGTH = 80
PREFIX = " * "
PREFIX_LENGTH = len(PREFIX)

def min_found(a, b):
	if a == -1 and b == -1:
		return (0)
	if b == -1:
		return a
	if a == -1:
		return b
	return min(a,b)

def get_doxygen_indents(lines):
	indent_main = 0
	indent_variable_block = 0
	in_variable_block = False

	for index, line in enumerate(lines):
		indent = 0
		cline = remove_doxygen_prefix(line)
		if line.strip()[-2:] == "*/":	
			return indent_main, indent_variable_block
		if not in_variable_block and has_variable(cline):
			in_variable_block = True
		if len(cline) == 0 or line[:2] == "**" or cline[0] != "@":
			continue
		if in_variable_block and cline[:len("@param")] == "@param":
			after_first_space = cline.find(" ") + 1
			indent = min_found(cline.find(" ", after_first_space), cline.find("\t", after_first_space))
		else:
			#print(cline, cline.find(" "), cline.find("\t"))
			indent = min_found(cline.find(" "), cline.find("\t"))
		indent = int(indent/4) + (indent % 4 != 0) + 1
			
		if in_variable_block:
			indent_variable_block = max(indent, indent_variable_block)
		else:
			indent_main = max(indent, indent_main)
			
		#print(cline, indent)


def break_doxygen_comments(lines: str) -> str:
	"""goes through all lines in a C file, checks for doxygen comments and
	breaks those comments in to a max line lenght of 80 chars while also
	aligning @keywords

	Args:
		lines (str): lines without formatted doxygen comments

	Returns:
		str: lines with formatted and broken doxygen comments
	"""
	new_lines = []
	in_comment = False
	in_variable_block = False
	buffer = ""
	
	for index, line in enumerate(lines):
		if index < len(lines) - 1:
			next_line = lines[index + 1]
			cnext_line = remove_doxygen_prefix(next_line)
		else:
			next_line = None
			cnext_line = None

		# print(in_comment, line)
		if not in_comment:
			if line.strip()[:3] == "/**":
				#index_end = find_end_of_comment_block(index, lines)
				indent_main, indent_variable_block = get_doxygen_indents(lines[index+1:])
				in_comment = True
				in_variable_block = False
				buffer = ""
			new_lines.append(line)
			continue
		else:
			cline = remove_doxygen_prefix(line)
			# print(cline)
			if line.strip()[-2:] == "*/":
				in_comment = False
				in_variable_block = False
				new_lines.append(line.strip())
				continue
			if not in_variable_block and has_variable(cline):
				in_variable_block = True
			# print(in_variable_block)
			if line[:2] == "**":
				new_lines.append(line.strip())
				continue
			# if in_variable_block:
			# 	new_lines.append(add_doxygen_prefix(cline))
			indent = indent_variable_block if in_variable_block else indent_main
			if cline != "":
				# print(cline)
				buffer = buffer + cline.strip() + " "
				# print("next: ", next_line)
				if next_line[:2] == "**" or cnext_line == "" or cnext_line[0] == "@" or next_line.strip()[-2:] == "*/" or (cnext_line[0].isnumeric() and cnext_line[1] == "."):
					if len(buffer) > 0:
						if buffer[0] != "@":
							indent = 0
						#print(buffer)
						buffer = split_buffer(buffer, new_lines, in_variable_block, indent)
						buffer = ""
			else:
				new_lines.append(add_doxygen_prefix(cline))
	return (new_lines)

def split_buffer(buffer: str, lines: list[str], in_variable_block: bool, indent: int) -> str:
	"""will take a new line and add it to the buffer. afterwards it will split
	the buffer and add each split to the variables lines until the buffer is
	smaller than the max line length minus the prefix length

	Args:
		buffer (str): buffer to add the new line to
		line (str): new line to add to the buffer
		lines (list[str]): list of lines to add to by splitting the buffer
		in_variable_block (bool): _description_
		indent (int): _description_
		first_line (bool): _description_

	Returns:
		str: _description_
	"""
	available = MAX_LINE_LENGTH - PREFIX_LENGTH - (indent - 1) * 4 - 1
	#print("indenting", indent, buffer)
	if buffer[0] == "@":
		if buffer[:len("@param")] == "@param":
			middle = min_found(buffer.find(" "), buffer.find("\t"))
		else:
			after_first_space = buffer.find(" ") + 1
			middle = min_found(buffer.find(" ", after_first_space), buffer.find("\t", after_first_space))

		prefix = buffer[0:middle]
		buffer_after = buffer[middle:].strip()
		indent_first = (indent - 1) * 4 - len(prefix) + 1
		#print(indent_first, int(indent_first / 4), (indent_first % 4 != 0))
		indent_first = int(indent_first / 4) + (indent_first % 4 != 0)

		#print(prefix, len(prefix), indent_first, indent, 4 * (indent - 1))
		buffer = split_to_length(buffer_after, lines, available, indent_first, prefix)
	while len(buffer.strip()) > 0:
		buffer = split_to_length(buffer, lines, available, indent, "")
	
	return buffer

def split_to_length(buffer, lines, available, indent, prefix):
	
	last_was_non_space = False
	previous_space = None
	non_space = None
	previous_non_space = None
	# indent_prefix = indent * 4 - len(prefix)
	# indent_prefix = int(indent_prefix / 4) + (indent_prefix % 4 != 0)
	# indent_prefix = prefix + "\t" * indent_prefix
	indent_prefix = prefix + "\t" * indent
	counter = 0
	for index, char in enumerate(buffer):
		if char == "\t":
			counter = counter + 4
		else:
			counter = counter + 1
		if char.isspace():
			if last_was_non_space:
				previous_non_space = non_space
				non_space = index - 1
				if counter + 1 > available:
					#print(add_doxygen_prefix(indent_prefix + buffer[:previous_non_space + 1].strip()))
					lines.append(add_doxygen_prefix(indent_prefix + buffer[:previous_non_space + 1].strip()))
					return buffer[previous_non_space + 1:].strip() + " "
			last_was_non_space = False
		else:
			last_was_non_space = True
	#print(add_doxygen_prefix(indent_prefix + buffer[:available].strip()))
	lines.append(add_doxygen_prefix(indent_prefix + buffer[:available].strip()))
	return buffer[available:].strip() + " "

def has_variable(line: str) -> bool:
	"""Checks if doxygen comment line has a parameter or return description

	Args:
		line (str): line to check for parameter or return description

	Returns:
		bool: returns True if line has a parameter or return description or False otherwise
	"""
	return line[:len("@param")] == "@param" or line[:len("@return")] == "@return"

def add_doxygen_prefix(line: str) -> str:
	"""Adds the C comment doxygen prefix to a line

	Args:
		line (str): line without C comment doxygen prefix

	Returns:
		str: line with C comment doxygen prefix
	"""
	return (" * " + line.rstrip())

def remove_doxygen_prefix(line):
	line = line.strip()
	if line != "" and line[0] == "*":
		line = line[1:]
	return (line.strip())




if __name__ == "__main__":
	test_comment = """
/**
 * @brief sort the items on stack_a using stack_b
 * 
 * The idea of double sort is to separate all items into two groups in stack_a
 * and stack_b (push_half_to_b) which are then put in order concurrently (stack_a sorted increasingly, 
 * stack_b sorted decreasingly) and finally joined, in order, on stack_a (push_back_to_a). 
 * There are to options to proceed: either push the smallest elements of stack_a
 * to stack_b or the largest elements. Both variants are tested (op1 and op2 
 * respectively) and are compared. The variant with the smallest number of oper-
 * ations is returend.
 * 
 * Compare the following:
 * 1. an apple
 * 2. a banana
 * 3. two banana
 * 
 * @param stack_a stack configuration to bring in order
 * @return t_ring* list of operations to sort stack_a using stack_b
 */


/**
 * @brief sort the items on stack_a using stack_b
 * 
 * The idea of double sort is to separate all items into two groups in stack_a
 * and stack_b (push_half_to_b) which are then put in order concurrently (stack_a sorted increasingly,
 * stack_b sorted decreasingly) and finally joined, in order, on stack_a (push_back_to_a).
 * There are to options to proceed: either push the smallest elements of stack_a
 * to stack_b or the largest elements. Both variants are tested (op1 and op2
 * respectively) and are compared. The variant with the smallest number of oper-
 * ations is returend.
 * 
 * @param stack_a stack configuration to bring in order
 * @return t_ring* list of operations to sort stack_a using stack_b
*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	if (n == 0)
		return (0);
	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	while (n > 1 && *str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
		n--;
	}
	return (*str1 - *str2);
}
/**
 * @brief sort the items on stack_a using stack_b
 * 
 * The idea of double sort is to separate all items into two groups in stack_a
 * and stack_b (push_half_to_b) which are then put in order concurrently (stack_a sorted increasingly,
 * stack_b sorted decreasingly) and finally joined, in order, on stack_a (push_back_to_a).
 * There are to options to proceed: either push the smallest elements of stack_a
 * to stack_b or the largest elements. Both variants are tested (op1 and op2
 * respectively) and are compared. The variant with the smallest number of oper-
 * ations is returend.
 * 
 * @param stack_a stack configuration to bring in order
 * @return t_ring* list of operations to sort stack_a using stack_b
*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	if (n == 0)
		return (0);
	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	while (n > 1 && *str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
		n--;
	}
	return (*str1 - *str2);
}
"""
	lines = test_comment.split("\n")
	new = break_doxygen_comments(lines)
	print("")
	print("printing parsed comments:")
	for index, line in enumerate(new):
		if len(line) < MAX_LINE_LENGTH + 1:
			line = line + (MAX_LINE_LENGTH - len(line)) * " " + "| " + str(len(line))
			new[index] = line
	print("\n".join(new))

	
#!python3
MAX_LINE_LENGTH = 80
PREFIX = " * "
PREFIX_LENGTH = len(PREFIX)

def break_doxygen_comments(lines):
	new_lines = []
	in_comment = False
	in_variable_block = False
	buffer = ""
	for index, line in enumerate(lines):
		if index < len(lines) - 1:
			next_line = remove_doxygen_prefix(lines[index + 1])
		else:
			next_line = None

		# print(in_comment, line)
		if line.strip()[:3] == "/**":
			#index_end = find_end_of_comment_block(index, lines)
			in_comment = True
			in_variable_block = False
			buffer = ""
			new_lines.append(line.strip())
			continue
		if in_comment:
			cline = remove_doxygen_prefix(line)
			# print(cline)
			if line.strip()[-2:] == "*/":
				in_comment = False
				new_lines.append(line.strip())
				continue
			if not in_variable_block and has_variable(cline):
				in_variable_block = True
			# print(in_variable_block)
			if in_variable_block:
				new_lines.append(add_doxygen_prefix(cline))
			else:
				if cline != "":
					# print(cline)
					buffer = split_with_buffer(buffer, cline, new_lines)
					# print("next: ", next_line)
					if next_line == "" or has_variable(next_line) or (next_line[0].isnumeric() and next_line[1] == "."):
						# print(buffer)
						# print(line)
						# print("")
						if len(buffer) > 0:
							if len(buffer) > MAX_LINE_LENGTH - PREFIX_LENGTH:
								buffer = split_with_buffer(buffer, cline, new_lines)
							new_lines.append(add_doxygen_prefix(buffer))
							buffer = ""
				else:
					new_lines.append(add_doxygen_prefix(cline))
		else:
			new_lines.append(line)
	return (new_lines)

def has_variable(line):
	return line[:len("@param")] == "@param" or line[:len("@return")] == "@return"

def add_doxygen_prefix(line):
	return (" * " + line.rstrip())

def remove_doxygen_prefix(line):
	line = line.strip()
	if line != "" and line[0] == "*":
		line = line[1:]
	return (line.strip())

def split_with_buffer(buffer, line, lines):
	available = MAX_LINE_LENGTH - PREFIX_LENGTH
	# print("buffer: ", buffer)
	buffer = buffer + line.strip() + " "
	while len(buffer) > available:
		buffer = split_to_length(buffer, lines, available)
	
	return buffer

def split_to_length(buffer, lines, available):
	
	last_was_non_space = False
	previous_space = None
	non_space = None
	previous_non_space = None
	for index, char in enumerate(buffer):
		if char.isspace():
			if last_was_non_space:
				previous_non_space = non_space
				non_space = index - 1
				if non_space + 1 > available:
					lines.append(add_doxygen_prefix(buffer[:previous_non_space + 1]))
					return buffer[previous_non_space + 1:].strip() + " "
			last_was_non_space = False
		else:
			last_was_non_space = True
	lines.append(add_doxygen_prefix(buffer[:available]))
	return buffer[available:].strip() + " "

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

	
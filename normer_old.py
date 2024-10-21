def norm_file_old(path, errors_before):

	

	# extract header



		

	lines = len(file)
	brackets = 0
	one_line_counter = 0


	in_multi_line = False

	# check all other problems
	for index, current in enumerate(file):


		
		







		line_new = []
		ppc = ""
		pc = ""
		nc = ""
		# remove consecutive spaces
		for i, c in enumerate(line):
			if c == '"':
				if quotes:
					quotes = False
				else:
					quotes = True
			if quotes:
				continue
			
			if i < len(line) - 1:
				nc = line[i + 1]
			else:
				nc = ""
			if c == " " and pc == " ":
				pass
			#elif c == "*" and pc != " ":
			# todo: check for function prototype, where tab is needed in front of "*"
			elif c == "," and nc != " ":
				line_new.append(c)
				line_new.append(" ")
			elif (c in "+-/*<>!") and nc == "=":
				if pc != " ":
					line_new.append(" ")
				line_new.append(c)
			elif c == "=":
				if pc != " " and pc not in "+-/*!=<>":
					line_new.append(" ")
				line_new.append(c)
				if nc != "=" and nc != " ":
					line_new.append(" ")
			elif c in ["+", "-", "/"] and \
			pc != "'" and pc != '"' and nc != "'" and nc != '"' and \
			not (c == "+" and (pc == "+" or nc == "+")) and \
			not (c == "-" and ((pc == "-" or nc == "-") or (pc == " " and ppc in "=,") or pc == "")) and \
			not (c == "/" and (pc == "/" or nc == "/")) and \
			not (c == "-" and (pc == "(" or nc == ">")):
						if not pc == " ":
							line_new.append(" ")
						line_new.append(c)
						if not nc == " ":
							line_new.append(" ")
			else:
				line_new.append(c)
				ppc = pc
			pc = c
		line = "".join(line_new)
		
		
		#check all but last
		if next_line is not None:
			# remove whitespace at beginning of block
			if previous == "{":
				if line == "":
					line = "\n"

			#check for brackets around return

*/

	

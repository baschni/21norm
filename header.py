import datetime
# todo: extract creator and creation time from original header and take to new one!

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

def create_header(filepath, user, email, ): #orig_user, orig_email, user_creation, time_creation):
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

def extract_header(lines):
	header = ""
	if sum([1 for line in lines[:11] if line[:2] == "/*" and line[-2:] == "*/"]) == 11:
		if lines[8].find("########.fr       ") != -1:
			header = lines[:11]
			lines_after_header = lines[11:]

	header = "\n".join(header) + "\n"
	return header, lines_after_header
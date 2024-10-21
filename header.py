# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    header.py                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: baschnit <baschnit@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/20 20:40:52 by baschnit          #+#    #+#              #
#    Updated: 2024/10/21 06:00:13 by baschnit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import datetime
import os

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

def create_header(filepath, user, email, orig_creation_date, orig_creation_user):
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
				content = os.path.basename(filepath)
			elif i == 5:
				content = "By: " + user + " <" + email + ">"
			elif i == 7:
				stamp = datetime.datetime.now().strftime("%Y/%m/%d %H:%M:%S")
				if orig_creation_date != "" and orig_creation_user != "":
					content = "Created: " + orig_creation_date + " by " + orig_creation_user
				else:
					content = "Created: " + stamp + " by " + user
			elif i == 8:
				content = "Updated: " + stamp + " by " + user
			space_after_content = SPACE_BEFORE_ASCII - SPACE_BEFORE_CONTENT - len(content)
			header += "/*" + " " * SPACE_BEFORE_CONTENT + content + " " * space_after_content + HEADER_ASCII[i] + "*/\n"
	return header

def extract_header(lines):
	header = ""
	created_date = ""
	created_user = ""
	lines_after_header = lines
	if sum([1 for line in lines[:11] if line[:2] == "/*" and line[-2:] == "*/"]) == 11:
		if lines[8].find("########.fr       ") != -1:
			pos_created = lines[7].find("Created: ")
			pos_created_by = lines[7].find(" by ")
			if pos_created != -1 and pos_created_by != -1 and len(lines[7]) == 80:
				pos_created = pos_created + len("Created: ")
				pos_created_by_user = pos_created_by + len(" by ")
				created_date = lines[7][pos_created:pos_created_by].strip()
				created_user = lines[7][pos_created_by_user:55].strip()
				header = lines[:11]
				lines_after_header = lines[11:]
				header = "\n".join(header) + "\n"
				
	return header, lines_after_header, created_date, created_user
	
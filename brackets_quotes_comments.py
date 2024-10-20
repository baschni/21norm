NO_OTHERS_INSIDE = 1

def find_outside (heap: str, needle: str, markers):
	"""searches a needle in heap while checking that
	the needle is not in between markers (e.g. brackets, quotes, ...)
	
	returns:
		the index of the needle if found or
		-1 if needle is not found
	"""
	count = {}
	for marker in markers:
		count[marker] = 0
	for index, c in enumerate(heap):
		for marker in markers:
			# TODO
			no_others_inside = [count[markr] for markr in markers \
					   if len(markr) == 3 and markr[2] == NO_OTHERS_INSIDE and markr != marker]
			if not sum(no_others_inside):
				if marker[0] == marker[1]:
					if heap[index:index + len(marker[0])] == marker[0]:
						if count[marker] == 1:
							count[marker] = 0
						else:
							count[marker] = 1	
				else:
					if heap[index:index + len(marker[0])] == marker[0]:
						count[marker] += 1
					elif heap[index:index + len(marker[1])] == marker[1]:
						count[marker] = max(count[marker] - 1, 0)
		if sum(count.values()) == 0:
			if heap[index:index + len(needle)] == needle:
				return index
	return -1

def check_for_comments(line, in_comment):
	if in_comment is None:
		in_comment = {"//": False, "/*": False}
	if in_comment["//"]:
		in_comment["//"] = False
	if find_outside(line, "//", [('"', '"', NO_OTHERS_INSIDE), ("'", "'", NO_OTHERS_INSIDE)]) != -1:
		in_comment["//"] = True
	if line[:2] == "/*":
		in_comment["/*"] = True
	if line[-2:] == "*/":
		in_comment["/*"] = False
	return in_comment


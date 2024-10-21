NO_OTHERS_INSIDE = 1

def get_markers_count(index_to_stop, heap, markers, mcount = None):
	if mcount == None:
		mcount = dict()
		for marker in markers:
			mcount[marker] = 0
	if index_to_stop is None:
		index_to_stop = len(heap)
	for index, _ in enumerate(heap):
		if index == index_to_stop:
			return mcount;
		for marker in markers:
			no_others_inside = [mcount[markr] for markr in markers \
					   if len(markr) == 3 and markr[2] == NO_OTHERS_INSIDE and markr != marker]
			if not sum(no_others_inside):
				if marker[0] == marker[1]:
					if heap[index:][:len(marker[0])] == marker[0]:
						if mcount[marker] == 1:
							mcount[marker] = 0
						else:
							mcount[marker] = 1	
				else:
					if heap[index:][:len(marker[0])] == marker[0]:
						mcount[marker] += 1
					elif heap[index][:len(marker[1])] == marker[1]:
						mcount[marker] = max(mcount[marker] - 1, 0)
	return mcount;

def find_outside (needle: str, heap: str, markers):
	"""searches a needle in heap while checking that
	the needle is not in between markers (e.g. brackets, quotes, ...)
	
	returns:
		the index of the needle if found or
		-1 if needle is not found
	"""
	for index, _ in enumerate(heap):
		count = get_markers_count(index, heap, markers)
		if sum(count.values()) == 0:
			if heap[index:][:len(needle)] == needle:
				return index
		
	return -1

def find_outside_quotes (needle: str, heap: str):
	return find_outside(needle, heap,  [('"', '"', NO_OTHERS_INSIDE), ("'", "'", NO_OTHERS_INSIDE)])

def check_for_comments(line, in_comment):
	if in_comment is None:
		in_comment = {"//": False, "/*": False}
	if in_comment["//"]:
		in_comment["//"] = False
	if find_outside("//", line, [('"', '"', NO_OTHERS_INSIDE), ("'", "'", NO_OTHERS_INSIDE)]) != -1:
		in_comment["//"] = True
	if line[:2] == "/*":
		in_comment["/*"] = True
	if line[-2:] == "*/":
		in_comment["/*"] = False
	return in_comment


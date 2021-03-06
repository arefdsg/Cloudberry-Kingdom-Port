from optparse import OptionParser
import os
import sys

root_directory = os.getcwd()

def parse_options():
	parser = OptionParser()
	parser.add_option('-d', '--directory', dest='directory',
					  help='set base directory to DIR', metavar='DIR')
	parser.add_option('-o', '--out', dest='header_file',
					  help='output to FILE', metavar='FILE')
					  
	(options, args) = parser.parse_args()
	
	if options.directory:
		global root_directory
		root_directory = options.directory
		
	if options.header_file:
		sys.stdout = open(options.header_file, 'w')
		
def build_tree(root):
	for dirname, dirnames, filenames in os.walk(root):
		for filename in filenames:
			if filename.endswith('.h'):
				relative_path = os.path.relpath(os.path.join(dirname, filename), root_directory)
				print('#include "' + relative_path + '"')

if __name__ == '__main__':
	parse_options()
	print('#ifndef SUPER_GLOBAL_HEADER_H')
	print('#define SUPER_GLOBAL_HEADER_H')
	print('')
	
	build_tree(root_directory)
	
	print('')
	print('#endif')
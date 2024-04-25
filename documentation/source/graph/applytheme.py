import pydot
import json
import argparse

VALIDE_EDGE = ["use","contain","inherit"]
VALIDE_NODE = ["interface","plain","namespace"]

def Parse_Theme(filepath):
	with open(filepath,'r') as f:
		return json.load(f)

def Apply_Theme(filepath: str,themepath: str):
	graphs = pydot.graph_from_dot_file(filepath)
	if(len(graphs) != 1):
		raise ValueError("expected dot file to only have one graphbut got : " + str(len(graphs)))
	Parse_Graph(graphs[0],Parse_Theme(themepath))
	graphs[0].write(filepath.rstrip('.dot')+"_themed.dot")

def Parse_Graph(graph: pydot.Graph, theme: dict):
	edges = graph.get_edges()
	nodes = graph.get_nodes()
	for edge in edges:
		if edge.get_style() is not None and edge.get_style() in VALIDE_EDGE :
			Edge_Transform(edge.get_style(),edge,theme)
		elif(edge.get_style() is not None):
			raise ValueError("expecte style to be inside the valide edge list but got: " + edge.get_style() + " for edge:" + edge.get_source() + "-" + edge.get_destination())
		else:
			raise ValueError("expect edge style not to be none for edge: " + str(edge.get_source()) + "-" + str(edge.get_destination()))

	for node in nodes:
		if node.get_style() is not None and node.get_style() in VALIDE_NODE :
			Node_Transform(node.get_style(),node,theme)
		elif(edge.get_style() is not None):
			raise ValueError("expecte style to be inside the valide node list but got: " + edge.get_style() + " for node:" + edge.get_name())
		else:
			raise ValueError("expect node style not to be none for edge: " + edge.get_name())


def Edge_Transform(name:str, edge: pydot.Edge,theme: dict):
	for attribute in pydot.EDGE_ATTRIBUTES:
		#Is_Writable = attribute == "style" or edge.__getattribute__("get_"+attribute)() is not None
		if(theme[name].get(attribute) is not None):
			edge.__getattribute__("set_"+attribute)(theme[name].get(attribute))

def Node_Transform(name:str, node: pydot.Node,theme: dict):
	for attribute in pydot.NODE_ATTRIBUTES:
		#Is_Writable = attribute == "style" or node.__getattribute__("get_"+attribute)() is not None
		if(theme[name].get(attribute) is not None):
			node.__getattribute__("set_"+attribute)(theme[name].get(attribute))

def _Parse_Args():
	parser = argparse.ArgumentParser(description='Parse a dot file to apply a theme file')
	parser.add_argument('dot_file', metavar='dot_file', type=str, help='the path to the dot file')
	parser.add_argument('theme_file', metavar='theme_file', type=str, help='the path to the theme file')
	return parser.parse_args()

if __name__ == "__main__":
	args = _Parse_Args()
	Apply_Theme(args.dot_file,args.theme_file)

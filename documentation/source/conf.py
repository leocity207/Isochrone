# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'Isochrone'
copyright = '2024, Léo Cluzel'
author = 'Léo Cluzel'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = [
	'sphinx.ext.graphviz',
    'sphinx.ext.autodoc'
]
pygments_style = 'sphinx'

templates_path = []#['_templates']
exclude_patterns = []



# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'groundwork'
html_static_path = []#['_static']

# -- GraphViz configuration ----------------------------------
graphviz_output_format = 'svg'
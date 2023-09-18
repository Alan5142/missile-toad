# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'missile_toad'
copyright = '2023, Missile Toad Team'
author = 'Missile Toad Team'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = [
    'sphinx.ext.autodoc',
    'sphinx.ext.intersphinx',
    'sphinx.ext.autosectionlabel',
    'sphinx.ext.todo',
    'sphinx.ext.coverage',
    'sphinx.ext.mathjax',
    'sphinx.ext.ifconfig',
    'sphinx.ext.viewcode',
    'sphinx.ext.inheritance_diagram',
    'breathe',
    'exhale',
    'sphinxcontrib.plantuml',
    'myst_parser',
    'sphinxcontrib.plantuml'
]

templates_path = ['_templates']
exclude_patterns = []

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_static_path = ['_static']

highlight_language = 'c++'

html_theme = 'sphinx_rtd_theme'

# -- Breathe configuration -------------------------------------------------

breathe_projects = {
    "missile_toad": "../build/docs/doxygen/xml"
}
breathe_default_project = "missile_toad"
breathe_default_members = ('members', 'undoc-members')
breathe_implementation_filename_extensions = ['.c', '.cc', '.cpp']

# -- Exhale configuration -------------------------------------------------
exhale_args = {
    # These arguments are required
    "containmentFolder":     "./api",
    "rootFileName":          "library_root.rst",
    "rootFileTitle":         "Missile Toad API",
    "doxygenStripFromPath":  "..",
    # Suggested optional arguments
    "createTreeView":        True,
    # TIP: if using the sphinx-bootstrap-theme, you need
    # "treeViewIsBootstrap": True,
}

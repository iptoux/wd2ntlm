# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'wd2ntlm'
copyright = '2024, Maik Roland Damm <iptoux>'
author = 'Maik Roland Damm <iptoux>'
release = 'Dec. 2023'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = ["myst_parser","sphinx_design"]


templates_path = ['_templates']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']



# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = "furo"
html_static_path = ['_static']

html_title = "wd2ntlm docs"

html_theme_options = {
    "announcement": "<em>Important</em> announcement!",
}

html_sidebars = {
    "**": [
        "sidebar/scroll-start.html",
        "sidebar/brand.html",
        "sidebar/search.html",
        "sidebar/navigation.html",
        "sidebar/ethical-ads.html",
        "sidebar/scroll-end.html",
    ]
}

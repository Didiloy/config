#je charge l'autoconfig
config.load_autoconfig()

#Je définie la page par défaut du navigateur
c.url.default_page = 'file:///home/dylan//.config/qutebrowser/pageAcceuil/index.html'
c.url.start_pages = 'file:///home/dylan//.config/qutebrowser/pageAcceuil/index.html'

#Je met le darkmode sur les site
# config.set("colors.webpage.darkmode.enabled", True)

config.bind('X', 'hint links spawn --detach mpv {hint-url}')

config.bind('gl', 'open google.com')

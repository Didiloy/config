set noerrorbells
set guicursor=
set tabstop=4 softtabstop=4
"tabstop et l'autre c'est pour les tabulations de 4 caracteres
set smartindent
set autoindent
set cindent
set shiftwidth=4
set expandtab
set nu
"nu c'est pour les numeros de ligne
set relativenumber
set smartcase
set noswapfile
set incsearch
set nowrap
set scrolloff=8
set laststatus=2
set noshowmode
set mouse=a
"laststatus et noshowmode c'est pour avoir la barre de statut du plug
"lightline.vim

call plug#begin('~/.vim/plugged')
Plug 'itchyny/lightline.vim'
Plug 'junegunn/vim-easy-align'
Plug 'ap/vim-css-color'
Plug 'preservim/nerdtree'
Plug 'MarcWeber/vim-addon-mw-utils'
Plug 'tomtom/tlib_vim'
Plug 'garbas/vim-snipmate'
Plug 'honza/vim-snippets'
Plug 'tomtom/tcomment_vim'
Plug 'adelarsq/vim-matchit'
Plug 'jiangmiao/auto-pairs'
" Plug 'gruvbox-community/gruvbox'
call plug#end()

""Je lance le plugin gruvbox
" colorscheme gruvbox
" highlight Normal guibg=bg
" highlight Normal guifg=fg

"Je lance le plugin matchit
packadd! matchit

"Je vais map ma leaderkey
let mapleader = "\<Space>"

"Je vais créer un keybind pour lancer nerdtree
noremap <C-n> :NERDTree<CR>

"raccourci pour quitter et save
nnoremap <leader>q :wq<CR>
nnoremap <leader>w :w<CR>

"raccourci pour les tab
nnoremap tn :tabnew<Space>
nnoremap tj :tabprev<CR>
nnoremap tk :tabnext<CR>
nnoremap th :tabfirst<CR>
nnoremap tl :tablast<CR>

"raccourci pour changer de fenetre quand c'est split
nnoremap <C-h> <C-w>h
nnoremap <C-j> <C-w>j
nnoremap <C-k> <C-w>k
nnoremap <C-l> <C-w>l

"raccourci pour snipmate
imap <C-j> <Plug>snipMateNextOrTrigger
smap <C-j> <Plug>snipMateNextOrTrigger 

"Raccourci pour easy-align
"raccourci pour le visual mode
vnoremap ga :EasyAlign <Space>
"raccourci pour le non visual mode
nnoremap ga :EasyAlign <Space>

"raccourci pour copier coller dans un autre programme
vmap <C-c> "+y
inoremap <C-v> "+p
nmap <C-v> "+p

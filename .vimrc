" Only Vim
if &compatible
  set nocompatible               " Be iMproved
endif

" Keybinds
map <C-p> :Files<CR>
map <C-_> <plug>NERDCommenterToggle
nmap <silent> cd :call CocAction('jumpDefinition', 'tabe')<CR>
map c y
map cl :noh<Enter>
nnoremap ; :
vnoremap ; :

" Theming
set termguicolors
silent! syntax enable
set background=dark
silent! colo ThemerVim

" General config stuff
filetype plugin on
set number
set hlsearch
set ignorecase
set smartcase
set backspace=indent,eol,start
set autoindent
set nostartofline
set ruler
set laststatus=1
set confirm
set visualbell
set t_vb=
set cmdheight=2
set number
set notimeout ttimeout ttimeoutlen=200
set mouse=a
set updatetime=300

" Tabs
set shiftwidth=2
set softtabstop=2
set expandtab

" Vim terminal
let g:terminal_ansi_colors = [
  \ "#161925", "#ED254E", "#71F79F", "#F9DC5C",
  \ "#00c1e4", "#7c4ded", "#7CB7FF", "#dcdfe4",
  \ "#161925", "#ED254E", "#71F79F", "#F9DC5C",
  \ "#00c1e4", "#7c4ded", "#7CB7FF", "#dcdfe4"
  \]

" Plug stuff
call plug#begin('~/.vim/plugged')
Plug 'preservim/nerdtree'
Plug 'neoclide/coc.nvim', {'branch': 'release'}
Plug 'Xuyuanp/nerdtree-git-plugin'
Plug 'airblade/vim-gitgutter'
Plug 'junegunn/fzf.vim'
Plug 'terryma/vim-multiple-cursors'
Plug 'preservim/nerdcommenter'
Plug 'tpope/vim-surround'
Plug 'luochen1990/rainbow'
Plug 'jiangmiao/auto-pairs'
call plug#end()

" Autostart
autocmd CursorHold * silent call CocActionAsync('highlight')
autocmd VimEnter * NERDTree 
autocmd VimEnter * wincmd p
autocmd bufenter * if (winnr("$") == 1 && exists("b:NERDTree") && b:NERDTree.isTabTree()) | q | endif

" coc color
hi Pmenu guifg=#dcdfe4
hi PmenuSel guibg=#00c1e4 guifg=#dcdfe4

" rainbow brackets
let g:rainbow_active = 1
let g:rainbow_conf = {
\	'guifgs': ['#7c4ded', '#7CB7FF', '#71F79F', '#00c1e4'],
\}

" Gitgutter
let g:gitgutter_sign_added = '+'
let g:gitgutter_sign_modified = 'M'
let g:gitgutter_sign_removed = '-'
let g:gitgutter_sign_removed_first_line = '-'
let g:gitgutter_sign_modified_removed = '-'

" Nerdtree
let g:NERDTreeGitStatusIndicatorMapCustom = {
    \ "Modified"  : "M",
    \ "Staged"    : "+",
    \ "Untracked" : "N",
    \ "Renamed"   : ">",
    \ "Unmerged"  : "=",
    \ "Deleted"   : "X",
    \ "Dirty"     : "M",
    \ "Clean"     : "C",
    \ 'Ignored'   : 'I',
    \ "Unknown"   : "?"
    \ }
let NERDTreeShowHidden=1

" Nerdcomment
let g:NERDSpaceDelims = 1
let g:NERDCreateDefaultMappings = 0

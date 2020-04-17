syntax on
set nu
set tabstop=4
set shiftwidth=4
set background=dark

map <C-A> ggVG"+y
map <F5> :call Run()<CR>
func! Run()
	exec "w"
	exec "!g++ -Wall % -o %<"
	exec "!./%<"
endfunc
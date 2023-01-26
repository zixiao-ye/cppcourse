;; emacs settings for all files in the repo
;; https://www.gnu.org/software/emacs/manual/html_node/emacs/Directory-Variables.html
((nil . ((indent-tabs-mode . nil)
         (tab-width . 4)))
 (cmake-mode . ((indent-tabs-mode . nil)))
 (c++-mode . ((c-file-style . "stroustrup")
              (c-file-offsets . ((innamespace . 0))))))

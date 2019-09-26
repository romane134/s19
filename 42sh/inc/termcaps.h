/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <smondesi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 14:42:33 by smondesi          #+#    #+#             */
/*   Updated: 2019/09/14 15:25:22 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAPS_H
# define TERMCAPS_H
# define TRUE 1
# define FALSE 0
# define COLOR_WHITE 7
# define COLOR_BLACK 0
# define COLOR_MAGENTA 5
# define MAJ_LEFT ";2D"
# define MAJ_RIGHT ";2C"
# define MAJ_UP ";2A"
# define MAJ_DOWN ";2B"

# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <fcntl.h>

enum					e_key_press
{
	KEY_NULL = 0,
	CTRL_C = 3,
	CTRL_D = 4,
	CTRL_R = 18,
	TAB = 9,
	ENTER = 10,
	ESC = 27,
	ARROW_1 = 27,
	ARROW_2 = 91,
	CTRL_MAJ_E_1 = -62,
	CTRL_MAJ_E_2 = -76,
	CTRL_MAJ_C_1 = -61,
	CTRL_MAJ_C_2 = -121,
	CTRL_MAJ_X_1 = -53,
	CTRL_MAJ_X_2 = -101,
	CTRL_MAJ_V_1 = -30,
	CTRL_MAJ_V_2 = -105,
	ARROW_UP = 66,
	ARROW_DOWN = 65,
	ARROW_LEFT = 68,
	ARROW_RIGHT = 67,
	HOME = 72,
	END = 70,
	MAJ = 49,
	BACKSPACE = 127,
	UP_ARR = 4283163,
	DOWN_ARR = 4348699,
	LEFT_ARR = 4479771,
	RIGHT_ARR = 4414235
};

typedef struct			s_termcaps
{
	char				*clearstr;
	char				*godown;
	char				*del_line;
	char				*del_allline;
	char				*gostart;
	char				*gotostr;
	char				*goleft;
	char				*goup;
	char				*goright;
	char				*curs_save;
	char				*curs_restore;
	struct termios		term;
	struct termios		term_restore;
	int					pos;
	size_t				history_pos;
	size_t				history_len;
	char				*last_cmd;
	int					cmd_len;
	int					cc_start;
	char				*tmp_select;
	char				*copy;
	int					edit_mode;
	char				*reset;
	char				*highlight_color;
	int					size;
	int					height;
	int					pos_height;
	int					display_option;
	char				*text_color;
	int					pos_line;
	int					path;
	char				bp[NAME_MAX];
	int					prev_pos;
	int					prev_cmd;
	int					research_mode;
	size_t				r_hist;
	int					auto_start;
	int					auto_end;

}						t_termcaps;

typedef struct			s_filename
{
	char				*file;
	struct s_filename	*next;
}						t_filename;

void	job(int nb);
/*
 ** TERMCAPS HEADERS
*/
int		isprintable(char *str);

/*
 ** autocomplete
*/
char					*autocomplete(char *cmd, t_termcaps *termcaps);
void					save_formated_file(struct dirent	*dent, char *buf,
		char *cmd, t_filename **fname);
int						ft_last_word(char *str);
int						ft_last_slash(char *cmd);
char					*path_to_open(char *cmd);
char					*ft_show_or_complete(t_filename *fname,
		char *cmd, char *path);
int						ft_strcmpstart(char *str, char *find);
t_filename				*ft_add_list(t_filename *li, char *data);
int						ft_list_lenght(t_filename *li);
char					*ft_last_ch(char *str);
void					ft_del_list(t_filename *li);
char					*autocomplete_command(char *cmd);
char					*autocomplete_path(char *cmd);
char					*autocompletion_var_home(char *cmd);
char					*autocompletion_dynamique(char *cmd);

/*
 ** cut_paste
*/
void					cut(t_termcaps *termcaps, char **cmd);
void					paste(t_termcaps *termcaps, char **cmd);
/*
 ** edit_line
*/
char					*remove_previous_char(char *str, t_termcaps *termcaps);
char					*remove_next_char(char *str, t_termcaps *termcaps);
char					*add_char(char *str, char *buff, t_termcaps *termcaps);
void					del_line(t_termcaps *termcaps);

/*
 ** highlight
*/
void					highlight(t_termcaps *termcaps);
void					reset_highlight(t_termcaps *termcaps);
void					print_highlight(t_termcaps *termcaps, char *cmd);
char					*cut_in_cmd(t_termcaps *termcaps, char *cmd);
/*
 ** history
*/
int						open_history_file(t_termcaps *termcaps);
char					*read_last_line(int pos);
void					add_in_history(t_termcaps *termcaps, char *cmd);
void					termcaps_histo(t_termcaps *termcaps, char **cmd, int i);
/*
 ** init
*/
int						term_init(t_termcaps *termcaps);
void					init_new_cmd(t_termcaps *termcaps, int opt_display);
void					get_termcaps(t_termcaps *termcaps);
/*
 ** keys.c
*/
void					arrow_key(char *buffer, t_termcaps *t, char **cmd);
void					key_tab(char **cmd, t_termcaps *termcaps);
void					backspace_key(char **cmd, t_termcaps *termcaps);

/*
 ** key2
*/
void					del_key(char **cmd, t_termcaps *termcaps);
char					*entre_key(t_termcaps *t, char *cmd, char **buffer);
void					maj_combi(t_termcaps *t, char *cmd, char *buffer);
void					maj_right(t_termcaps *t, char *cmd);
void					alt_maj(t_termcaps *termcaps, char **cmd, char *buffer);

/*
** key3
*/
void					left_key(t_termcaps *t, char **cmd);
void					right_key(t_termcaps *t, char **cmd);

/*
 ** move
*/
void					go_left(t_termcaps *termcaps, char **cmd);
void					go_right(t_termcaps *termcaps, char **cmd);
void					down_one_line(t_termcaps *t);

/*
** termcaps_main
*/
void					which_key(char *buffer, char **cmd, t_termcaps *t);
char					*termcaps_main(t_termcaps *termcaps, int opt_display);
void					term_reset(t_termcaps *termcaps);

/*
 ** show
*/
void					show_new(char *cmd, t_termcaps *termcaps, int i);
int						display_name(void);
int						only_arrow(void);
void					choose_display(t_termcaps *termcaps);

/*
** recherche
*/
char					*result_reasearch(char *old_cmd, t_termcaps *t);
char					*result_reasearch_without_termcaps(char *old_cmd);

#endif

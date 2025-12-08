/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhh <jhh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 18:51:08 by jhijazi           #+#    #+#             */
/*   Updated: 2025/12/08 12:29:31 by jhh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "minishell.h"

int		checker(t_token *tok);
t_cmd	*check_parse(t_token *head);
int	    is_redir(t_token *tok);
void	handle_redir(t_token **token, t_cmd *cmd);
t_cmd	*create_cmd(void);
void	add_cmd_to_list(t_cmd **list, t_cmd *new_cmd);
void	free_cmd_list(t_cmd *cmd_list);

#endif

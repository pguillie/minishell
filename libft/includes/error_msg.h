/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 10:28:23 by pguillie          #+#    #+#             */
/*   Updated: 2017/09/19 16:54:33 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MSG_H
# define ERROR_MSG_H

# define E_2FWARG "Too few arguments"
# define E_2MNARG "Too many arguments"
# define E_ALNUM "String must contain alphanumeric characters"
# define E_ARGREQ "Option requires an argument"
# define E_ILLOPT "Illegal option"
# define E_NOCMD "Command not found"
# define E_NOENT "No such file or directory"
# define E_NOENV "Variable not found"
# define E_NOGNL "Cannot get input"
# define E_NOMEM "Not enought space"
# define E_NOOLDPWD "No previous directory"
# define E_NOOPEN "Cannot open file"
# define E_NORGHT "Permission denied"
# define E_NOTERM "Terminal type not defined"
# define E_NOTSET "Varibale not set"
# define E_RAW "Could not switch to non-canonical mode"
# define E_SETENV(var) "Unable to set `"var"' environemnent variable"
# define E_SYNERR "Syntax error near unexpected token"
# define E_TCBASE "Could not access the termcap data base"
# define E_TERMIOS "Could not restore previous structure"

#endif

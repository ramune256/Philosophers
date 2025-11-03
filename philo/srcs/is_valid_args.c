/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 14:21:09 by shunwata          #+#    #+#             */
/*   Updated: 2025/10/20 14:21:42 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_valid_args(int argc, char **argv)
{
	// ここに引数の数や内容（数字か、正の数か）をチェックする処理を追加
	(void)argv;
	if (argc < 5 || argc > 6)
	{
		printf("Error: Invalid number of arguments\n");
		return (false);
	}
	return (true);
}

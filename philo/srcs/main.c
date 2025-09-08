/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:55:08 by shunwata          #+#    #+#             */
/*   Updated: 2025/09/08 18:13:07 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// 引数が正しいかチェックする関数
static int	is_valid_args(int argc, char **argv)
{
	// ここに引数の数や内容（数字か、正の数か）をチェックする処理を追加
	// (このガイドでは簡略化)
	if (argc < 5 || argc > 6)
	{
		printf("Error: Invalid number of arguments\n");
		return (0);
	}
	return (1);
}

int main(int argc, char **argv)
{
	t_table	table;

	if (!is_valid_args(argc, argv))
		return (1);

	// TODO: cleanup(&table) でリソース解放

	if (init_table(&table, argv) != 0)
		return (1); // TODO: エラー処理とリソース解放

	table.start_time = get_time();
	for (int i = 0; i < table.num_philos; i++)
	{
		// 各哲学者のスレッドを作成
		pthread_create(&table.philos[i].thread, NULL, &philo_routine, &table.philos[i]);
	}

	for (int i = 0; i < table.num_philos; i++)
	{
		// 各哲学者のスレッドが終了するのを待つ
		pthread_join(table.philos[i].thread, NULL);
	}

	printf("Simulation will start soon...\n");
	return (0);
}

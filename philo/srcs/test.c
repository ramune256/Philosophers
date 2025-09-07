/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 22:33:41 by shunwata          #+#    #+#             */
/*   Updated: 2025/09/07 22:43:13 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>

int count = 0;
pthread_mutex_t lock; // Mutex変数を宣言

void *routine(void *arg)
{
    for (int i = 0; i < 1000000; i++)
    {
        pthread_mutex_lock(&lock);   // 鍵をかける
        count++;
        pthread_mutex_unlock(&lock); // 鍵を開ける
    }
    return (NULL);
}

int main(void)
{
    pthread_t t1, t2;

    pthread_mutex_init(&lock, NULL); // Mutexを初期化

    pthread_create(&t1, NULL, &routine, NULL);
    pthread_create(&t2, NULL, &routine, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock); // Mutexを破棄

    printf("Final count: %d\n", count); // 2000000になるはず
    return (0);
}

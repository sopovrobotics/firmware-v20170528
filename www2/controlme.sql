-- phpMyAdmin SQL Dump
-- version 4.6.6deb4
-- https://www.phpmyadmin.net/
--
-- Хост: localhost:3306
-- Время создания: Сен 14 2017 г., 11:26
-- Версия сервера: 5.7.19-0ubuntu0.17.04.1
-- Версия PHP: 7.0.22-0ubuntu0.17.04.1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- База данных: `controlme`
--

-- --------------------------------------------------------

--
-- Структура таблицы `users`
--

CREATE TABLE `users` (
  `id` int(4) NOT NULL,
  `login` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  `role` varchar(10) NOT NULL,
  `dt` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Дамп данных таблицы `users`
--

INSERT INTO `users` (`id`, `login`, `password`, `role`, `dt`) VALUES
(1, 'user1', '356a192b7913b04c54574d18c28d46e6395428ab', 'user', '2017-09-10 22:29:04'),
(2, 'user2', '356a192b7913b04c54574d18c28d46e6395428ab', 'user', '2017-09-10 22:29:24'),
(3, 'admin', 'd033e22ae348aeb5660fc2140aec35850c4da997', 'admin', '2017-09-10 22:32:08'),
(4, '123', '40bd001563085fc35165329ea1ff5c5ecbdbbeef', 'user', '2017-09-10 22:44:27');

-- --------------------------------------------------------

--
-- Структура таблицы `users_scripts`
--

CREATE TABLE `users_scripts` (
  `id` int(4) NOT NULL,
  `userid` int(11) NOT NULL,
  `script` text NOT NULL,
  `status` varchar(255) NOT NULL,
  `time_exec` int(11) NOT NULL,
  `result` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Дамп данных таблицы `users_scripts`
--

INSERT INTO `users_scripts` (`id`, `userid`, `script`, `status`, `time_exec`, `result`) VALUES
(1, 1, 'forward(100); // forward 100ms\nbackward(200); // backward 200ms\nturnleft(400); // turn to the left 400ms\nturnright(400); // turn to the right 400ms\n				', 'revoke', 0, 0),
(2, 1, 'forward(100); // forward 100ms\nbackward(200); // backward 200ms\nturnleft(400); // turn to the left 400ms\nturnright(400); // turn to the right 400ms\n				', 'revoke', 0, 0),
(3, 1, 'forward(100); // forward 100ms\nbackward(200); // backward 200ms\nturnleft(400); // turn to the left 400ms\nturnright(400); // turn to the right 400ms\n				', 'revoke', 0, 0),
(4, 1, 'forward(100); // forward 100ms\nbackward(200); // backward 200ms\nturnleft(400); // turn to the left 400ms\nturnright(400); // turn to the right 400ms\n				', 'revoke', 0, 0),
(5, 1, 'forward(100); // forward 100ms\nbackward(200); // backward 200ms\nturnleft(400); // turn to the left 400ms\nturnright(400); // turn to the right 400ms\n				', 'revoke', 0, 0),
(6, 1, 'forward(100); // forward 100ms\nbackward(200); // backward 200ms\nturnleft(400); // turn to the left 400ms\nturnright(400); // turn to the right 400ms\n				', 'revoke', 0, 0),
(7, 1, 'forward(100); // forward 100ms\nbackward(200); // backward 200ms\nturnleft(400); // turn to the left 400ms\nturnright(400); // turn to the right 400ms\n				', 'revoke', 0, 0),
(8, 1, 'forward(100); // forward 100ms\nbackward(200); // backward 200ms\nturnleft(400); // turn to the left 400ms\nturnright(400); // turn to the right 400ms\n				', 'revoke', 0, 0),
(9, 1, 'dl;sfak;dskfdsakf', 'revoke', 0, 0);

--
-- Индексы сохранённых таблиц
--

--
-- Индексы таблицы `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `login_idx` (`login`);

--
-- Индексы таблицы `users_scripts`
--
ALTER TABLE `users_scripts`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT для сохранённых таблиц
--

--
-- AUTO_INCREMENT для таблицы `users`
--
ALTER TABLE `users`
  MODIFY `id` int(4) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;
--
-- AUTO_INCREMENT для таблицы `users_scripts`
--
ALTER TABLE `users_scripts`
  MODIFY `id` int(4) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=10;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

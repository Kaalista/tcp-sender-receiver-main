# tcp-sender-receiver-main

Написать серверную часть, которая будет работать как демон и принимать соединения от клиентов.
Для этого можно использовать сокеты, создавая TCP-сокет на сервере и слушая его на определенном порту.
Можно создать класс-обертку над сокетами, чтобы работать с ними удобнее.

Для обработки сигналов SIGTERM и SIGHUP в демоне нужно установить соответствующие обработчики сигналов.
Сигнал SIGTERM нужен для корректного завершения демона при получении сигнала от системы, 
а сигнал SIGHUP можно использовать для перезагрузки конфигурационных файлов или других настроек демона без его остановки.

Написать клиентскую часть, которая будет читать данные из текстового файла и передавать их по TCP-соединению на сервер.
Для этого также нужно использовать сокеты.
Написать код для сохранения принятых данных на сервере в файл. 

Например, можно создать текстовый файл на сервере и записывать в него принятые данные по мере их получения.
По возможности, добавить обработку ошибок и исключений в код, чтобы приложение работало более надежно.
Протестировать приложение, запустив серверную часть как демон и подключив к ней клиентскую часть для передачи текстового файла. 
Убедиться, что данные успешно передаются и сохраняются на сервере.
Это общий план реализации, конкретные детали зависят от требований к приложению. 

Создали папку для выполнения лабораторной работы №9
В папке добавили файл README.md
Закоммитили изменение
![alt text](image.png) 
Отправили в репозиторий изменения 
Ввели логин и Personal Access Token (PAT) для авторизации в аккаунте GitHab
![alt text](image-1.png)
Работа через VS Code
![alt text](image-2.png)

![alt text](image-3.png)
На оценку 3:
1. Используйте git status, чтобы узнать, на какой ветке вы находитесь.
![alt text](image-4.png)
2. Как выглядит git log? 
![alt text](image-5.png)
3. Создайте файл sort.c и вставьте туда код функции любой сортировки 
(только ф-ия сортировки) 
![alt text](image-6.png)
4. Как сейчас выглядит вывод git status? 
![alt text](image-7.png)
5. Добавьте файл в область stage (add) 
6. Как сейчас выглядит git status? 
![alt text](image-8.png)
7. Закоммитить файл в репозиторий 
![alt text](image-9.png)
8. Как сейчас выглядит git status? 
![alt text](image-10.png)
9. Добавить комментарий с любым текстом в этот же файл 
![alt text](image-11.png)
10.  Как сейчас выглядит git status? 
![alt text](image-12.png)   
11.  Добавьте (add) изменение файла 
12.  Как сейчас выглядит git status? 
![alt text](image-14.png)
13.  Измените файл еще раз (можно добавить еще комментарий или убрать 
старый)
![alt text](image-15.png)
14.  Сделайте коммит 
![alt text](image-16.png)
15.  Как сейчас выглядит status? Журнал (log)?
![alt text](image-17.png)
16.  Добавьте в stage и закоммитьте последнее изменение
![alt text](image-18.png)
17.  Запушим на удаленный репо (git push) 
![alt text](image-19.png)
Ветки.  
1. Используйте git branch mybranch (или git checkout -b mybranch), чтобы 
создать новую ветку с именем mybranch. 
![alt text](image-20.png)
2. Снова используйте git branch, чтобы увидеть новую созданную ветку.![alt text](image-21.png)
3. Используйте git switch mybranch (или git checkout mybranch), чтобы 
переключиться на новую ветку. 
![alt text](image-22.png)
4. Как изменяется вывод git status при переключении между master и новой 
веткой, которую вы создали? 
 в выводе git status изменилось название активной ветки с main на mybranch
![alt text](image-23.png)
5. Убедитесь, что вы находитесь на своей ветке mybranch, прежде чем 
продолжить. 
6. Создайте файл с именем file1.txt и своим именем. 
![alt text](image-24.png)
7. Добавьте файл и закоммитьте это изменение. ![alt text](image-25.png)
8. Используйте git log --oneline --graph, чтобы увидеть, что ваша ветка 
указывает на новый коммит. 
1. Вернитесь к ветке с именем master. 
2.  Используйте git log --oneline --graph, что изменилось? 
3.  Создайте новый файл с именем file2.txt и закоммитьте его. 
4.  Используйте git log --oneline --graph --all, чтобы увидеть, что ваша ветка 
указывает на новый коммит, и что теперь у двух веток разные коммиты. 
1.  Переключитесь на вашу ветку mybranch. 
2.  Наш file2.txt пропал? 
3.  Используйте git diff mybranch master, чтобы увидеть разницу между 
двумя ветками. 
1.   Добавить текстовый документ со скриншотами в ветку mybranch. 
Закоммитить и запушить на удаленный репо ветку mybranch (git push -u 
origin mybranch) 
1.   Убедиться, что в github.com две ветки master и mybranch. Не забыть 
запушить изменения master ветки в master
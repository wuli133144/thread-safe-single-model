
## document

##### why i create this thread-safe-single-model

>recently i find some horrible thing happened when db server GetInstance() have been called,the reason why disaster come out, I was unable to find it util today .there was a thread-safe issue. Getinstance() must run in single-thread enviroment,otherwise ,maybe some unpredictied things will happen,and it's hard to find it,so please ensure that all project run in single-thread enviroment,if you want to put it in  multi-thread ,just use lastest version,






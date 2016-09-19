ps aux |grep  Lobby |grep cmio|grep pts |grep -v grep |awk '{print $2}' |xargs kill -9

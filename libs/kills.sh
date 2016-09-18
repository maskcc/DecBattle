ps aux |grep  Lobby |grep jinpan|grep pts |grep -v grep |awk '{print $2}' |xargs kill -9

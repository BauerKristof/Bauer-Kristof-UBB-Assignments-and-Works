#include "message.h"

mqd_t initalizeClientQueue(){
	int flags_ = O_RDWR | O_CREAT;	//flagek beállítása
	mode_t mode_  = 0666;	//jogok beállítása
	struct mq_attr attr_;	//struktura létrehozása és beállítása
	attr_.mq_flags   = 0;
	attr_.mq_maxmsg  = 10;
	attr_.mq_msgsize = sizeof(serverMsg);
	attr_.mq_curmsgs = 0;
	char mqClient[MAXSIZE];
	sprintf(mqClient, "%s_%d", MQ_CLIENT, getpid());
	// printf("%s\n", mqClient);
	mqd_t clientQid = mq_open(MQ_CLIENT, flags_, mode_, &attr_);	//Üzenetsor létrehozása
	if (clientQid == -1){
		perror("mq_open():");
		exit(1);
	}
	return clientQid;
}

mqd_t initalizeServerQueue(){
	int flags = O_RDWR;	//flagek beállítása
	mqd_t serverQid = mq_open(MQ_SERVER, flags);	//Üzenetsor megnyitása
	if (serverQid <0){
		perror("Failed to open the message queue");
		exit(1);
	}
	return serverQid;
}

int main(int argc, char* argv[])
{
	if(argc < 3){
		printf("Hasznalat: %s <day> <hour1> <hour2>\n", argv[0]);
		exit(1);
	}
	mqd_t clientQid = initalizeClientQueue();
	printf("megnyitva a kliens \n" );

	srandom(time(0));
	printf("Client tries to send a message...\n");
	char day[3], hour1[6], hour2[6];
	clientMsg client_msg;
	strcpy(client_msg.day, argv[1]);
	strcpy(client_msg.hour1, argv[2]);
	strcpy(client_msg.hour2, argv[3]);


	printf("client_msg = (%s, %s, %s)\n", client_msg.day, client_msg.hour1, client_msg.hour2);
	int prio = random() % MQ_PRIO_MAX;

	int flags = O_RDWR;	//flagek beállítása

	mqd_t serverQid = initalizeServerQueue();



	if (mq_send(serverQid, (char*) &client_msg, sizeof(clientMsg), 3) == -1) //üzenet küldése
	{
		perror("Failed to send msg");
		exit(1);
	}
	else{
		printf("Kliens:Informacio elkuldve...\n");

		serverMsg server_msg = {""};


		while(strcmp(server_msg.row, "-1")!=0)  //válasz fogadása
		{
			if(mq_receive(clientQid, (char*) &server_msg, sizeof(serverMsg), 0) == -1)
			{
				perror("mq_receive");
				return(1);
			}
			if(strcmp(server_msg.row, "-1")!=0){
				printf("%s", server_msg.row);
			}
		}


	}
	mq_close(serverQid);
	mq_close(clientQid);	//üzenetsor bezárása
	mq_unlink(MQ_CLIENT);	//üzenetsor törlése

	return 0;
}

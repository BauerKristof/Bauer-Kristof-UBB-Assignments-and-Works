#include "message.h"

int main(int argc, char* argv[])
{

      int flags = O_RDWR | O_CREAT;	//flagek beállítása
      mode_t mode  = 0666;	//jogok beállítása

      struct mq_attr attr;	//struktura létrehozása és beállítása
      attr.mq_flags   = 0;
      attr.mq_maxmsg  = 10;
      attr.mq_msgsize = sizeof(clientMsg);
      attr.mq_curmsgs = 0;

      mqd_t serverQid = mq_open(MQ_SERVER, flags, mode, &attr);	//Üzenetsor létrehozása

      if (serverQid == -1){
            perror("server_mq_open():");
            exit(1);
      }
      printf("megnyitottam a sajat mqueue-mat\n");


      clientMsg client_msg = {"","",""};
      serverMsg server_msg = {""};
      unsigned int priority = 0;

      int flags_ = O_RDWR;	//flagek beállítása
      mqd_t clientQid;


      if (mq_receive(serverQid, (char*) &client_msg, sizeof(clientMsg), NULL) != -1){ //Üzenet fogadása
            printf("Szerver:Megkaptam az informaciot\n");
            clientQid = mq_open(MQ_CLIENT, flags_);	//Üzenetsor megnyitása
            if (clientQid <0){
                  perror("Failed to open the message queue");
                  exit(1);
            }
            char command[MAXSIZE];
            char answer[MAXSIZE];
            FILE * f;

            sprintf(command, "./bkim1790_lab5.sh %s %s %s", client_msg.day, client_msg.hour1, client_msg.hour2);

            if((f = popen(command, "r"))==NULL){
                  perror("popen error");
                  exit(1);
            }

            while(fgets(answer, MAXSIZE*sizeof(char), f)){
                  printf("%s", answer);
                  strcpy(server_msg.row, answer);
                  if (mq_send(clientQid, (char*) &server_msg, sizeof(serverMsg), priority) == -1){ //válasz küldése
                        perror("Failed to send msg");
                        exit(1);
                  }
            }
            strcpy(server_msg.row, "-1");

            if (mq_send(clientQid, (char*) &server_msg, sizeof(serverMsg), priority) == -1){ //válasz küldése
                  perror("Failed to send msg");
                  exit(1);
            }
            printf("elkuldom a kilepot\n");
      }
      else{
            perror("mq_receive");
            exit(1);
      }

      mq_close(serverQid);	//üzenetsor bezárása
      mq_close(clientQid);
      mq_unlink(MQ_SERVER);
      return 0;
}

/*
 *  Copyright (C) Boost.Asio를 이용한 네트워크 프로그래밍 - 한빛출판네트워크
 *
 *  Client Protocol:  google cpplint and maintained by Paran Lee <p4ranlee@gmail.com>
 *
 */
#include <cstdint>
const unsigned int16_t PORT_NUMBER = 31400;

const int MAX_RECEIVE_BUFFER_LEN = 512;

const int MAX_NAME_LEN = 17;
const int MAX_MESSAGE_LEN = 129;

struct PACKET_HEADER {
    int16_t nID;
    int16_t nSize;
};

const int16_t REQ_IN = 1;         // PKT_REQ_IN
const int16_t RES_IN = 2;         // PKT_RES_IN
const int16_t REQ_CHAT = 6;       // PKT_REQ_CHAT
const int16_t NOTICE_CHAT = 7;    // PKT_NOTICE_CHAT

struct PKT_REQ_IN : public PACKET_HEADER {
    void Init() {
        nID = REQ_IN;
        nSize = sizeof(PKT_REQ_IN);
        memset(szName, 0, MAX_NAME_LEN);
    }

    char szName[MAX_NAME_LEN];
};

struct PKT_RES_IN : public PACKET_HEADER {
    void Init() {
        nID = RES_IN;
        nSize = sizeof(PKT_RES_IN);
        bIsSuccess = false;
    }

    bool bIsSuccess;
};

struct PKT_REQ_CHAT : public PACKET_HEADER {
    void Init() {
        nID = REQ_CHAT;
        nSize = sizeof(PKT_REQ_CHAT);
        memset(szMessage, 0, MAX_MESSAGE_LEN);
    }

    char szMessage[MAX_MESSAGE_LEN];
};

struct PKT_NOTICE_CHAT : public PACKET_HEADER {
    void Init() {
        nID = NOTICE_CHAT;
        nSize = sizeof(PKT_NOTICE_CHAT);
        memset(szName, 0, MAX_NAME_LEN);
        memset(szMessage, 0, MAX_MESSAGE_LEN);
    }

    char szName[MAX_NAME_LEN];
    char szMessage[MAX_MESSAGE_LEN];
};

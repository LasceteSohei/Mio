// Mio.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

extern "C"
{
#include "libavcodec\avcodec.h"
#include "libavformat\avformat.h"
#include "libswscale\swscale.h"

}

#pragma comment(lib, "avcodec.lib")

using namespace std;

int main(int argc, char **argv)
{
	cout << "Testing ffmpeg library...." << endl;

	/*!< Initialize library*/
	avcodec_register_all();

	/*!< Structure containing all the informations/metadata from the file*/
	AVFormatContext *pFormatCtx = NULL;

	/*!< Opening our video file*/
	if (avformat_open_input(&pFormatCtx, argv[1], NULL, NULL) != 0)
		return -1; // Cannot open file
	/*!< Only open the header, now we need to take a look at the stream itself*/

	/*!< Getting stream informations*/
	if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
		return -1; // Couldn't find stream info
	/*!< In order to look at this info, check pFormatCtx->streams */

	/*!< Handy funcion for debugging*/
	av_dump_format(pFormatCtx, 0, argv[1], 0);

	/*!< Finding the video stream*/
	int videostream = -1;
	for (int i = 0; i < pFormatCtx->nb_streams ; i++) 
	{
		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			videostream = i;
			break;
		}
	}
	if (videostream == -1)
		return -1; // No video stream inside babe

	/*!< Codec context is the information about the codec used by the video*/
	AVCodecContext *pCodecCtxOrig = NULL;
	AVCodecContext *pCodecCtx = pFormatCtx->streams[videostream]->codec;

	AVCodec *pCodec = NULL;

	/*!< Find the decoder for the video stream*/
	pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
	if (pCodec == NULL)
	{
		cout << "Error: Unsupported codec" << endl;
		return -1; // Codec not found
	}

	/*!< Copy context*/
	pCodecCtx = avcodec_alloc_context3(pCodec);
	if (avcodec_copy_context(pCodecCtx, pCodecCtxOrig) != 0)
	{
		cout << "Error: Couldn't copy codec context" << endl;
		return -1;
	}

	/*!< Open Codec*/
	if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0)
		return -1; // Couldn't open codec


	
	cout << "Done..." << endl;
    return 0;
}


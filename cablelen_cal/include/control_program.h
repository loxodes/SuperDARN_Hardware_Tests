#include <pthread.h>
#include <sys/time.h>
#include "tsg.h"

#ifndef _CONTROL_PROGRAM_H
#define _CONTROL_PROGRAM_H

#define ROS_IP "127.0.0.1"
#define ROS_PORT 45000


struct BadTR {

  unsigned int *start_usec;
  unsigned int *duration_usec;
  int length;
};


struct ControlData {
  int samples;
  unsigned int *main;
  unsigned int main_address;
  unsigned int *back;
  unsigned int back_address;
  int shm_memory;
  int status;
  int frame_header;
  int bufnum;
  int *agc;
  int *lopwr;
  struct BadTR bad_transmit_times;
  unsigned long event_secs;
  unsigned long event_nsecs;

};

struct RadarPRM {
     int site;
     int radar; //required: DO NOT SET MANUALLY
     int channel; //required: DO NOT SET MANUALLY
};

struct RXFESettings {
     int ifmode;  // IF Enabled
     int amp1;    // Stage 1 Amp 20 db before IF mixer
     int amp2;    // Stage 2 Amp 10 db after IF mixer
     int amp3;    // Stage 3 Amp 10 db after IF mixer
     int att1;    // 1/2 db Attenuator
     int att2;    //  1  db Attenuator
     int att3;    //  2  db Attenuator 
     int att4;    //  4  db Attenuator
};

struct ChannelStatus {
     int active;
};

struct SiteSettings {
     char name[80];
     int num_radars;
     struct RXFESettings rxfe_settings;  /* reciever front end settings for this site */
//     struct DDSSettings dds_settings;  
//     struct PhasingSettings phasing_settings;  
//     struct RecvSettings phasing_settings;  
};


struct ControlPRM {
     char name[80]; //optional: but a very good idea to set
     char description[120]; //optional: but a very good idea to set
     int radar; //required: DO NOT SET MANUALLY
     int channel; //required: DO NOT SET MANUALLY
     int local;  //if local use shared memory for data handling else use tcp
     int priority; //optional: valid 0-99: lower value higher priority when running multiple operational programs
     int current_pulseseq_index; //required: registered pulse sequence to use 
// transmit beam definition one of these needs to be non-zero
     int tbeam;  //required: valid 0-31: defines standard look directions 
     unsigned int tbeamcode; //optional: used for special beam directions, used only if beam is invalid value.
// Imaging transmit beam options
     float tbeamazm; //optional: used for imaging radar
     float tbeamwidth; //optional: used for imaging radar
//transmit setup
     int tfreq;  //required: transmit freq in kHz 
     int trise;  // required: rise time in microseconds
//reciever setup
     int number_of_samples;  //required: number of recv samples to collect 
     int buffer_index; //required: valid 0-1: DMA buffer to use for recv
     double baseband_samplerate; //required: normally equals (nbaud/txpl) but can be changed for oversampling needs
     int filter_bandwidth; //required: normally equals basebad_samplerate but can be changed for oversampling needs
     int match_filter;  // required: valid 0-1: whether to use match filter, normally equal 1 
     int rfreq;  //optional: if invalid value tfreq is used
// reciever beam definitions: only used if tbeam is invalid
     int rbeam;  //optional: valid 0-31: defines standard look directions: if invalid tbeam is used 
     unsigned int rbeamcode; //optional: used for special beam directions, used only if rbeam and tbeam is invalid value.
// Imaging receiver beam options
     float rbeamazm; //optional: used for imaging radar
     float rbeamwidth; //optional: used for imaging radar
// ROS Feedback
     int status; // coded value: non-zero values will code to an error msg
};

struct ROSMsg {
     char type;
     int status;
};

struct CLRFreqPRM {
     int start; //In kHz
     int end;  //in kHz
     double filter_bandwidth;  //in kHz  typically c/(rsep*2)
     double pwr_threshold;  //  typical value 0.9: power at best available frequency must be 90% or less of current assigned 
     int nave;  // Number of passes to average.
};
//ROSMsg type definitions:
#define SET_RADAR_CHAN 'R'
#define SET_INACTIVE 'a'
#define SET_ACTIVE 'A'
#define GET_SITE_SETTINGS 's'
#define UPDATE_SITE_SETTINGS 'S'
#define GET_PARAMETERS 'c'
#define SET_PARAMETERS 'C'

#define PING '='
#define OKAY '^'
#define NOOP '~'
#define QUIT '.'

#define REGISTER_SEQ '+'
#define REMOVE_SEQ '-'

#define REQUEST_ASSIGNED_FREQ '>'
#define REQUEST_CLEAR_FREQ_SEARCH '<'
#define LINK_RADAR_CHAN 'L'

#define SET_READY_FLAG '1'
#define UNSET_READY_FLAG '!'
#define SET_PROCESSING_FLAG '2'
#define UNSET_PROCESSING_FLAG '@'

#define GET_DATA 'd'

#endif

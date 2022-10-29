#ifdef LOG_H
#define LOG_H

// Open log file.
void
open_log(char *filename)
// Write message to log.
void
log(const char *format, ...);
// Return file pointer of current log file stream.
FILE *
get_logfile_ptr();
// Includes graphic object into log file.
void
include_graph(char *path);
// Close current log file stream.
void
close_log();
// Close log file and open it in Firefox automatically.
void
view_log(char *filename);

#endif // LOG_H


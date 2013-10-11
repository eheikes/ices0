#include <stdio.h>
#include "definitions.h"
#include "metadata.h"
#include "icestypes.h"
#include "id3.h"

#define INPUT_BUFSIZ 4096


/* open up path, figure out what kind of input it is, and set up source */
static int
stream_open_source (input_stream_t* source)
{
  char buf[INPUT_BUFSIZ];
  size_t len;
  int fd;
  int rc;

  source->filesize = 0;
  source->bytes_read = 0;
  source->channels = 2;

  if (source->path[0] == '-' && source->path[1] == '\0') {
    ices_log_debug("Reading audio from stdin");
    fd = 0;
  } else if ((fd = open (source->path, O_RDONLY)) < 0) {
    ices_util_strerror (errno, buf, sizeof (buf));
    ices_log_error ("Error opening: %s", buf);

    return -1;
  }

  source->fd = fd;

  if ((rc = lseek (fd, 0, SEEK_END)) >= 0) {
    source->filesize = rc;
    lseek (fd, 0, SEEK_SET);
  }

  if ((len = read (fd, buf, sizeof (buf))) <= 0) {
    ices_util_strerror (errno, buf, sizeof (buf));
    //ices_log_error ("Error reading header: %s", source->path, buf);
	ices_log_error ("Error reading header: %s", source->path);

    close (fd);
    return -1;
  }

#ifdef HAVE_LIBFLAC
  if (!(rc = ices_flac_open (source, buf, len)))
    return 0;
  if (rc < 0) {
    close(fd);
    return -1;
  }
#endif

#ifdef HAVE_LIBFAAD
  if (!(rc = ices_mp4_open (source, buf, len)))
    return 0;
  if (rc < 0) {
    close(fd);
    return -1;
  }
#endif

  if (!(rc = ices_mp3_open (source, buf, len)))
    return 0;
  if (rc < 0) {
    close (fd);
    return -1;
  }

#ifdef HAVE_LIBVORBISFILE
  if (!(rc = ices_vorbis_open (source, buf, len)))
    return 0;
#endif

  close (fd);
  return -1;
}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("You must specify a filename\n");
		return 1;
	}
	
	input_stream_t source;
	source.path = argv[1];
    ices_metadata_set (NULL, NULL);
    ices_metadata_set_file (source.path);
    if (stream_open_source (&source) < 0)
	{
		printf("stream_open_source() returned an error\n");
		ices_util_free (source.path);
	}
	
	printf("\ndone.\n");
	return 0;
}

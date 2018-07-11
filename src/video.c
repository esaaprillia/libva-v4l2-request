/*
 * Copyright (C) 2018 Paul Kocialkowski <paul.kocialkowski@bootlin.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
 * IN NO EVENT SHALL PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>

#include <linux/videodev2.h>
#include <drm_fourcc.h>

#include "video.h"
#include "utils.h"

static struct video_format formats[] = {
	{
		.description		= "NV12 YUV",
		.v4l2_format		= V4L2_PIX_FMT_NV12,
		.v4l2_buffers_count	= 1,
		.drm_format		= DRM_FORMAT_NV12,
		.drm_modifier		= DRM_FORMAT_MOD_NONE,
		.drm_planes_count	= 2,
		.bpp			= 16,
	},
	{
		.description		= "MB32-tiled NV12 YUV",
		.v4l2_format		= V4L2_PIX_FMT_MB32_NV12,
		.v4l2_buffers_count	= 1,
		.drm_format		= DRM_FORMAT_NV12,
		.drm_modifier		= DRM_FORMAT_MOD_ALLWINNER_MB32_TILED,
		.drm_planes_count	= 2,
		.bpp			= 16
	},
};

static unsigned int formats_count = sizeof(formats) / sizeof(formats[0]);

struct video_format *video_format_find(bool tiled_format)
{
	unsigned int pixelformat;
	unsigned int i;

	pixelformat = video_v4l2_format(tiled_format);

	for (i = 0; i < formats_count; i++)
		if (formats[i].v4l2_format == pixelformat)
			return &formats[i];

	return NULL;
}

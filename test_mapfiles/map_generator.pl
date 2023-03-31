# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    map_generator                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csharrie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/20 19:28:33 by csharrie          #+#    #+#              #
#    Updated: 2023/03/20 19:28:41 by csharrie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/usr/bin/perl

use warnings;
use strict;

die "program x y density" unless (scalar(@ARGV) == 3);

my ($x, $y, $density) = @ARGV;

print "$y.ox\n";
for (my $i = 0; $i < $y; $i++) {
	for (my $j = 0; $j < $x; $j++) {
		if (int(rand($y) * 2) < $density) {
			print "o";
		}
		else {
			print ".";
		}
	}
	print "\n";
}

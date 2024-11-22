package Mech;
use common::sense;
use autodie;
use vars qw( @ISA );
use WWW::Mechanize::Shell;
our(@ISA)=qw( WWW::Mechanize);
use HTTP::CookieJar::LWP;
use Nobody::Util;

sub new {
  my($class)=class(shift);
  my($cjar) = new HTTP::CookieJar::LWP;
  my($mech) = WWW::Mechanize::new($class, cookie_jar => $cjar);
  $mech;
};
sub next_file() {
  my ($num,$file)=1;
  for($file) {
    $_=sprintf("con-%04d.html",$num);
    warn("$_\n");
    last unless -e;
    ++$num;
  };
  open(my $hand, ">", $file);
  $hand;
}
sub get {
  my ( $self, $url ) = (shift,shift);
  $DB::single=1;
  @_=$self->SUPER::get($url,@_);
  ddx(\@_);
  my $hand=next_file();
  $hand->print($self->content);
  $self;
};
sub parse {
  my $self=shift;
  my $html=$self->content;
  use HTML::TokeParser;
  my $tokp=HTML::TokeParser->new($html);
  $tokp;
};
1;

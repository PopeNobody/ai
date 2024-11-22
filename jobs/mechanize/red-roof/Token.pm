#!/usr/bin/perl

{
  package Token;
}

{
  package TokType;
  our(@keys) = qw( code tag 
  our(@text) = (qw(
    S  tag attr attrseq           text
    E  tag                        text
    T                             text is_data
    C                             text
    D                             text
    PI                     token0 text
    )
  );
  package Token;
  use Nobody::Util;
  use common::sense;
  our(%type);
  sub new {
    my $class=class(shift);
    my $self=shift;
    return $self unless defined $self;
    die( "expected array" ) unless ref($self) eq 'ARRAY';
    for($self->[0]){
      $_=$type{$_};
      bless($self, join('::',$class,$_));
    };
  };
  sub type {
    my $self=shift;
    my $type=$self->[0];
    $type{$type};
  };
  sub attr {
    my $self=shift;
    my $type=$self->type;
    die "attrs only exist in 'beg' tokens" unless $type eq 'beg';
    my $attr=$self->[1];
    $attr;
  };
}
};
{
  package TokType;
  our(%type);
	     ["S",  $tag, $attr, $attrseq, $text]
	     ["E",  $tag, $text]
	     ["T",  $text, $is_data]
	     ["C",  $text]
	     ["D",  $text]
	     ["PI", $token0, $text]
};

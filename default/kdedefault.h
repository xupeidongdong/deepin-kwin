#ifndef __KDECLIENT_H
#define __KDECLIENT_H

#include <qbutton.h>
#include <qbitmap.h>
#include <kpixmap.h>
#include "../client.h"
class QLabel;
class QSpacerItem;
class QHBoxLayout;


// get rid of autohide :P
class KDEDefaultClientButton : public QButton
{
public:
    KDEDefaultClientButton(int w, int h, Client *parent=0, const char *name=0,
                 const unsigned char *bitmap=NULL);
    void setBitmap(const unsigned char *bitmap);
    void reset();
    QSize sizeHint() const;
    int last_button;

protected:
    void mousePressEvent( QMouseEvent* e )
    {
	last_button = e->button();
	QMouseEvent me ( e->type(), e->pos(), e->globalPos(), LeftButton, e->state() );
	QButton::mousePressEvent( &me );
    }
    void mouseReleaseEvent( QMouseEvent* e )
    {
	last_button = e->button();
	QMouseEvent me ( e->type(), e->pos(), e->globalPos(), LeftButton, e->state() );
	QButton::mouseReleaseEvent( &me );
    }
    virtual void drawButton(QPainter *p);
    void drawButtonLabel(QPainter *){;}
    QSize defaultSize;
    QBitmap deco;
    Client *client;
};

class KDEClient : public Client
{
    Q_OBJECT
public:
    enum Buttons{BtnHelp=0, BtnSticky, BtnMax, BtnIconify, BtnClose};
    KDEClient( Workspace *ws, WId w, QWidget *parent=0, const char *name=0 );
    ~KDEClient(){;}
protected:
    void resizeEvent( QResizeEvent* );
    void paintEvent( QPaintEvent* );
    void showEvent( QShowEvent* );
    void windowWrapperShowEvent( QShowEvent* );
    void mouseDoubleClickEvent( QMouseEvent * );
    void init();
    void captionChange( const QString& name );
    void stickyChange(bool on);
    void maximizeChange(bool m);
    void doShape();
    void activeChange(bool);

    void calcHiddenButtons();
    void updateActiveBuffer( bool force = false );
protected slots:
    void slotReset();
    void slotMaximize();
private:
    KDEDefaultClientButton* button[5];
    QSpacerItem* titlebar;
    bool hiddenItems;
    QHBoxLayout *hb;
    KPixmap activeBuffer;
};




#endif

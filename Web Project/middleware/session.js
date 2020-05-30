// middleware az engedélyezéshez
exports.authorize = (roles = ['felhasznalo', 'admin', 'guest']) => (req, res, next) => {
  if (!req.session.role) {
    // a felhasználó nincs bejelentkezve
    req.session.role = 'guest';
    next();
  } else if (!roles.includes(req.session.role)) {
    // a felhasználó be van jelentkezve de nincs joga ehhez az operációhoz
    const err = 'You do not have permission to access this endpoint';
    let userInfo = '';
    if (req.session.role === 'guest') {
      userInfo = 'guest';
    } else {
      userInfo = req.session.username;
    }
    res.status(401).render('error', { message: `Error: ${err}`, userInfo });
  } else {
    // minden rendben
    next();
  }
};

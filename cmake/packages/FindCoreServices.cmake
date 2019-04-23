# Locate CoreServices
# This module defines
# CORESERVICES_LIBRARY
# CORESERVICES_FOUND

IF(APPLE)
  SET(CORESERVICES_FOUND "YES")
  find_library(CORESERVICES_LIBRARY CoreServices)
ELSE(APPLE)
  SET(CORESERVICES_FOUND "NO")
ENDIF(APPLE)
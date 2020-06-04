FUNCTION almost_equal(x, gold, tol) RESULT(b)
    implicit none
    REAL, intent(in) :: x
    INTEGER,  intent(in) :: gold
    REAL,     intent(in) :: tol
    LOGICAL              :: b
    b = ( gold * (1 - tol)  <= x ).AND.( x <= gold * (1+tol) )
END FUNCTION almost_equal
PROGRAM target_teams_distribute__parallel__do
    LOGICAL :: almost_equal
    INTEGER :: N_i = 64
    INTEGER :: i
    INTEGER :: N_j = 64
    INTEGER :: j
    REAL :: counter = 0
!$OMP TARGET TEAMS DISTRIBUTE REDUCTION(+: counter) MAP(TOFROM: counter) 
    DO i = 1 , N_i
!$OMP PARALLEL REDUCTION(+: counter)
!$OMP DO
    DO j = 1 , N_j
counter = counter +  1.
    END DO
!$OMP END PARALLEL
    END DO
IF ( .NOT.almost_equal(counter, N_i*N_j, 0.1) ) THEN
    WRITE(*,*)  'Expected', N_i*N_j,  'Got', counter
    CALL EXIT(112)
ENDIF
END PROGRAM target_teams_distribute__parallel__do